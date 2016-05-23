#!/usr/bin/env python3
import asyncio
import functools
import queue
import serial
import signal
import simplejson as json
from serial.threaded import LineReader, ReaderThread
from serial.tools import list_ports
from aiohttp import ClientSession, ClientOSError, Timeout

_stop = False
url = "https://embedded16.duckdns.org/phplibs/api.php"
from_arduino = queue.Queue()
REMOTE = "remote"
ARDUINO = "arduino"


def connect_arduino():
    try:
        arduino_port = list(list_ports.grep('2341:0043'))[0][0]
    except IndexError:
        print('Arduino is not connected!')
    else:
        arduino = serial.Serial(arduino_port,
                                9600,
                                parity=serial.PARITY_NONE,
                                stopbits=serial.STOPBITS_ONE,
                                bytesize=serial.EIGHTBITS)
        arduino.setDTR(False)
        import time
        time.sleep(0.022)
        arduino.flushInput()
        arduino.flushOutput()
        arduino.setDTR(True)
        return arduino


class PrintLines(LineReader):
    global from_arduino

    def connection_made(self, transport):
        super(PrintLines, self).connection_made(transport)
        self.ready = False
        self.daemon = True

    def handle_line(self, data):
        if data == "Pronto!":
            self.ready = True
        else:
            from_arduino.put(data)

    def get_message_queue(self):
        return self.from_arduino

    def connection_lost(self, exc):
        print('Port Closed!')


async def get_token():
    data = {'gimme': 'cookie'}
    try:
        session = ClientSession()
        with Timeout(0.8):
            async with session.post(url, data=data) as response:
                return {'sessionID': response.cookies['sessionID'].value}
    finally:
        session.close()


async def send_post(data, cookie):
    global _stop
    try:
        with Timeout(0.7):
            async with ClientSession(cookies=cookie) as session:
                async with session.post(url, data=data) as response:
                    if response.status == 200:
                        response.json()
    except (ClientOSError, Timeout):
        print("Connection problem.")
        _stop = True


def parse_json(data):
    msg = f = t = ""
    try:
        data = json.loads(data)
        msg = data.get('msg')
        f = data.get('from')
        t = data.get('to')
    except ValueError:
        pass
    else:
        return (msg, f, t)


def printm(msg, f, t):
    print('Message {} from {} from {}'.format(msg, t, f))


async def dispatch(cookie, protocol):
    global _stop, from_arduino
    while not _stop:
        data = from_arduino.get()
        msg, f, t = parse_json(data)
        if all(k is not None for k in (msg, f, t)):
            if t == ARDUINO:
                protocol.write_line(data)
            if t == REMOTE:
                await send_post(data, cookie)


async def main(loop):
    arduino = connect_arduino()
    reader_arduino = ReaderThread(arduino, PrintLines)
    reader_arduino.daemon = True
    reader_arduino.start()
    m, writer = reader_arduino.connect()
    cookie = await get_token()
    if cookie is not None:
        disp_coro = asyncio.ensure_future(dispatch(cookie, writer))
        await asyncio.wait([disp_coro], loop=loop)


def end(loop):
    global _stop
    _stop = True


if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    for signame in ('SIGINT', 'SIGTERM'):
        loop.add_signal_handler(
            getattr(signal, signame), functools.partial(end, loop))
    print("Ctrl-C to close the program...")
    try:
        loop.run_until_complete(asyncio.ensure_future(main(loop)))
    finally:
        loop.close()
        print("Bye!", flush=True)
