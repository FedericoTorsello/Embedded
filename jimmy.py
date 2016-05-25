#!/usr/bin/env python3
import asyncio
import signal
import ujson as json
import utils
from serial.threaded import ReaderThread
from aiohttp import ClientSession, ClientOSError, Timeout

_stop = False
url = 'https://embedded16.duckdns.org/phplibs/api.php'


async def get_token(user, pwd):
    h = {'content-type': 'application/json'}
    data = json.dumps({'request': 'auth', 'username': user, 'password': pwd})
    with Timeout(0.8):
        async with ClientSession() as session:
            async with session.post(url, data=data, headers=h) as response:
                if 'sessionID' in response.cookies:
                    return {'sessionID': response.cookies['sessionID'].value}
                else:
                    utils.print('Wrong Credentials!', 1)


async def send_post(data, cookie):
    global _stop
    try:
        h = {'Content-Type': 'application/json'}
        data = {'request': 'test'}
        data = json.dumps(data)
        with Timeout(0.7):
            async with ClientSession(cookies=cookie, headers=h) as session:
                async with session.post(url, data=data) as response:
                    if response.status == 200:
                        print(await response.json())
                    else:
                        utils.print('Error on request', 1)
                        _stop = True
    except (ClientOSError, Timeout):
        utils.print('Connection problems.', 1)
        _stop = True


async def dispatch(cookie, protocol):
    global _stop
    from_arduino = protocol.get_message_queue()
    while not _stop:
        data = from_arduino.get()
        msg, f, t = utils.parse_json(data)
        if all(k is not None for k in (msg, f, t)):
            if t == utils.ARDUINO:
                protocol.write_line(data)
            if t == utils.REMOTE:
                await send_post(data, cookie)
        await asyncio.sleep(.001)

async def main(loop):
    user, pwd = utils.read_inputs()
    cookie = await get_token(user, pwd)
    arduino = utils.connect_arduino()
    if all(k is not None for k in (arduino, cookie)):
        reader_arduino = ReaderThread(arduino, utils.PrintLines)
        reader_arduino.daemon = True
        reader_arduino.start()
        rt, printlines = reader_arduino.connect()
        user = pwd = None
        disp_coro = asyncio.ensure_future(dispatch(cookie, printlines))
        await asyncio.wait([disp_coro], loop=loop)


def end():
    global _stop
    _stop = True


if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    for signame in ('SIGINT', 'SIGTERM'):
        loop.add_signal_handler(
            getattr(signal, signame), end)
    utils.print('Ctrl-C to close the program...')
    try:
        loop.run_until_complete(asyncio.ensure_future(main(loop)))
    finally:
        loop.close()
        utils.print('Bye!')
