#!/usr/bin/env python3
import asyncio
import functools as ft
import signal
import ujson as json
import utils
from serial.threaded import ReaderThread
from aiohttp import ClientSession, ClientOSError, Timeout, TCPConnector

"""""" """""" """""" """""" """""" """""" """""" """""" ""
" This script reads from the serial port messages from   "
" Arduino and forwards them to te recipient              "
" specified in the message protocol field.               "
" Async IO (with aiohttp) library guarantees high        "
" performance execution of IO tasks without using lots   "
" of system resources.                                   "
""" """ """ """ """ """ """ """ """ """ """ """ """ """ ""

_stop = False
user = None
url = 'https://embedded16.duckdns.org/phplibs/api.php'


async def get_token(user, pwd):
    """Returns the authentication token from the server API if login parameter are correct."""
    global _stop
    # Set the header content-type for HTTP request
    h = {'Content-Type': 'application/json'}
    # Convert data to JSON format
    data = json.dumps({'request': 'auth', 'username': user, 'password': pwd})
    try:
        with Timeout(0.8):
            async with ClientSession() as session:
                async with session.post(url, data=data, headers=h) as response:
                    if 'sessionID' in response.cookies:
                        # Read and return cookie value from HTTP response
                        return {'sessionID':
                                response.cookies['sessionID'].value}
                    else:
                        utils.print('Wrong Credentials!', 1)
                        _stop = True
    except (ClientOSError, Timeout):
        utils.print('Timeout Connection', 1)
        _stop = True


async def send_post(data, cookie, queue):
    """Send a POST request to the server."""
    global _stop
    try:
        h = {'Content-Type': 'application/json'}
        data = json.dumps(data)
        with Timeout(1):
            async with ClientSession(cookies=cookie, headers=h) as session:
                async with session.post(url, data=data):
                    pass
    except:
        pass


async def dispatch(cookie, protocol):
    """Parse the messages from Arduino and dispatch them to the recipients."""
    global _stop
    # Retrieve the queue of messages from Arduino
    from_arduino = protocol.get_message_queue()
    last_distance = 0
    last_status = 0
    # Prepare standard messages
    data_distance = {'request': 'distance', 'msg': None, 'username': user}
    data_code = {'request': 'status', 'msg': None, 'username': user}
    while not _stop:
        # Pop a JSON message from the queue or wait for it
        try:
            data = from_arduino.get()
        except TypeError:
            pass
        else:
            # Parse the message and get payload informations
            f, t, msg, payload = utils.parse_json(data)
            if all(k is not None for k in (msg, f, t, payload)):
                if t == utils.ARDUINO:
                    # Send message to Arduino
                    protocol.write_line(data)
                    await asyncio.sleep(0.3)
                if t == utils.REMOTE:
                    # Send message to serer API with HTTP request
                    if msg == 'distance' and (payload > (last_distance + 2) or
                                              payload < (last_distance - 2)):
                        last_distance = data_distance['msg'] = payload
                        await send_post(data_distance, cookie, from_arduino)
                    if msg == 'status' and payload != last_status:
                        last_status = data_code['msg'] = payload
                        await send_post(data_code, cookie, from_arduino)
                if t == utils.LOCAL or t == 'debug':
                    # Print the message
                    utils.print(msg)


async def main(loop):
    """Init all variables and starts routines"""
    global user
    user, pwd = utils.read_inputs()
    cookie = await get_token(user, pwd)
    pwd = None
    # Connect to serial
    arduino = utils.connect_arduino()
    if all(k is not None for k in (arduino, cookie)):
        try:
            # Starts a reader thread (pyserial with asyncio support is still in development)
            reader_arduino = ReaderThread(arduino, utils.PrintLines)
            reader_arduino.start()
            rt, printlines = reader_arduino.connect()
            # Handler signal from system
            for signame in ('SIGINT', 'SIGTERM'):
                loop.add_signal_handler(
                    getattr(signal, signame),
                    ft.partial(end, printlines))
            # Create a coroutine to run into asyncio loop
            disp_coro = asyncio.ensure_future(dispatch(cookie, printlines))
            # Run the coroutine and wait
            await asyncio.wait([disp_coro])
        except Exception as e:
            print(type(e).__name__)
        finally:
            end(printlines)


def end(protocol):
    """Called when an error occour to stop the program."""
    global _stop
    data = {'msg': 'stop', 'from': 'python', 'to': 'arduino'}
    protocol.write_line(json.dumps(data))
    _stop = True


if __name__ == '__main__':
    # Get the default asyncio event loop
    loop = asyncio.get_event_loop()
    utils.print('Ctrl-C to close the program...')
    try:
        # Start the program
        loop.run_until_complete(main(loop))
    finally:
        # Gracefully shutdown the loop
        loop.close()
        utils.print('Bye!')
