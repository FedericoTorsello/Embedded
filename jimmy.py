#!/usr/bin/env python3
import asyncio
import functools as ft
import re
import signal
import ujson as json
import utils
from serial.threaded import ReaderThread
from aiohttp import ClientSession, ClientOSError, Timeout

_stop = False
user = None
url = 'https://embedded16.duckdns.org/phplibs/api.php'


async def get_token(user, pwd):
    global _stop
    h = {'content-type': 'application/json'}
    data = json.dumps({'request': 'auth', 'username': user, 'password': pwd})
    with Timeout(0.8):
        async with ClientSession() as session:
            async with session.post(url, data=data, headers=h) as response:
                if 'sessionID' in response.cookies:
                    return {'sessionID': response.cookies['sessionID'].value}
                else:
                    utils.print('Wrong Credentials!', 1)
                    _stop = True


async def send_post(data, cookie, queue):
    global _stop
    try:
        h = {'Content-Type': 'application/json'}
        data = {'request': 'test'}
        data = json.dumps(data)
        with Timeout(0.7):
            async with ClientSession(cookies=cookie, headers=h) as session:
                async with session.post(url, data=data) as response:
                    if response.status == 200:
                        d = await response.json()
                        queue.put(d)
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
        try:
            data = from_arduino.get()
        except:
            pass
        else:
            msg, f, t = utils.parse_json(data)
            if all(k is not None for k in (msg, f, t)):
                print(msg, f, t)
                if t == utils.REMOTE:
                    await send_post(data, cookie, from_arduino)
                if t == utils.LOCAL:
                    utils.print(msg)

async def main(loop):
    global user
    user, pwd = utils.read_inputs()
    cookie = await get_token(user, pwd)
    pwd = None
    arduino = utils.connect_arduino()
    if all(k is not None for k in (arduino, cookie)):
        try:
            reader_arduino = ReaderThread(arduino, utils.PrintLines)
            reader_arduino.start()
            rt, printlines = reader_arduino.connect()
            for signame in ('SIGINT', 'SIGTERM'):
                loop.add_signal_handler(getattr(signal, signame), ft.partial(end, printlines))
            data = {'msg': 'start', 'from': 'python', 'to': 'arduino'}
            printlines.write_line(json.dumps(data))
            disp_coro = asyncio.ensure_future(dispatch(cookie, printlines))
            await asyncio.wait([disp_coro])
        finally:
            end(printlines)


def end(protocol):
    global _stop
    data = {'msg': 'stop', 'from': 'python', 'to': 'arduino'}
    protocol.write_line(json.dumps(data))
    _stop = True


if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    utils.print('Ctrl-C to close the program...')
    try:
        loop.run_until_complete(main(loop))
    finally:
        loop.close()
        utils.print('Bye!')
