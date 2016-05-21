import argparse
import asyncio
import getpass
import queue
import serial
import simplejson as json
import sys
import threading
from queue import Queue
from time import sleep
from serial.threaded import LineReader
from serial.tools import list_ports
from aiohttp import ClientSession
from aiohttp import Timeout

ARDUINO = "arduino"
LOCAL = "local"
REMOTE = "remote"

LOCAL = "python"
from_arduino = Queue()
to_remote = asyncio.Queue()

url = "https://embedded16.duckdns.org/phplibs/api.php"


def connect_arduino():
    try:
        arduino_port = list(list_ports.grep('2341:0043'))[0][0]
    except IndexError:
        print('Arduino is not connected!')
        sys.exit(-1)
    else:
        arduino = serial.Serial(arduino_port,
                                9600,
                                parity=serial.PARITY_NONE,
                                stopbits=serial.STOPBITS_ONE,
                                bytesize=serial.EIGHTBITS)
        arduino.flushInput()
        arduino.flushOutput()
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
        import traceback
        traceback.print_exc(exc)
        print('Port Closed!')


class WriteWorker(threading.Thread):

    def __init__(self, s):
        super(WriteWorker, self).__init__()
        self.daemon = True
        self.rw = s
        self.msg_queue = queue.Queue()

    def append_message(self, msg):
        self.msg_queue.put(msg)
        if not self.isAlive():
            self.run()

    def run(self):
        while not self.msg_queue.empty():
            try:
                data = self.msg_queue.get() + '\n'
                self.rw.write(data.encode('ascii'))
                sleep(0.4)
            except queue.Empty:
                break


def parse_json(data):
    try:
        data = json.loads(data)
        msg = data.get('msg')
        f = data.get('from')
        t = data.get('to')
    except ValueError:
        pass
    else:
        return (msg, f, t)


def parse_args():
    class read_password(argparse.Action):

        def __call__(self, parser, namespace, values, option_string):
            if values is None:
                values = getpass.getpass()
            setattr(namespace, self.dest, values)

    parser = argparse.ArgumentParser(description='User Authentication.')
    parser.add_argument('-p', action=read_password, nargs='?', dest='user')


async def get_token():
    data = {'gimme': 'cookie'}
    with Timeout(5):
        async with ClientSession() as session:
            async with session.post(url, data=data) as response:
                try:
                    return {'sessionID': response.cookies['sessionID'].value}
                except KeyError:
                    print('Wrong credentials!')


async def send_post():
    cookie = await get_token()
    while True:
        d = await to_remote.get()
        with Timeout(5):
            async with ClientSession(cookies=cookie) as s:
                async with s.post(url, data=d) as response:
                    r = await response.json()
                    print(r)


loop = asyncio.get_event_loop()
loop.create_task(send_post())
