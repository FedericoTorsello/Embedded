"""Module library for JimmyChallenge main script (jimmy.py)."""
import builtins
import getpass
import serial
import queue
import ujson as json
from colored import fore, style
from serial.tools import list_ports
from serial.threaded import LineReader


REMOTE = 'remote'
ARDUINO = 'arduino'


"""Extend LineReader from pyserial library."""
class PrintLines(LineReader):
    def connection_made(self, transport):
        super(PrintLines, self).connection_made(transport)
        self.from_arduino = queue.Queue()

    def handle_line(self, data):
        # Parse message from Arduino, if JSON add to queue
        try:
            data = json.loads(data)
        except ValueError:
            pass
        else:
            self.from_arduino.put(data)

    def get_message_queue(self):
        # Return the queue of messages
        return self.from_arduino

    def connection_lost(self, exc):
        # When an exception occour close the program
        print('Port Closed!', 1)
        import os
        os._exit(1)


def print(msg, t=0):
    """Wrapper of builtin python print function."""
    if t == 0:
        builtins.print(fore.BLUE + style.BOLD + msg + style.RESET)
    if t == 1:
        builtins.print(fore.RED + style.BOLD + msg + style.RESET)


def connect_arduino():
    """Connect to serial and reset the Arduino to start a new game."""
    try:
        arduino_port = list(list_ports.grep('2341:0043'))[0][0]
    except IndexError:
        print('Arduino is not connected!', 1)
    else:
        arduino = serial.Serial(arduino_port,
                                9600,
                                parity=serial.PARITY_NONE,
                                stopbits=serial.STOPBITS_ONE,
                                bytesize=serial.EIGHTBITS)
        # Change state of DTR to reset arduino
        arduino.setDTR(False)
        import time
        # Wait for 22ms (from Arduino specs)
        time.sleep(.022)
        arduino.flushInput()
        arduino.flushOutput()
        arduino.setDTR(True)
        return arduino


def parse_json(data):
    """Parse the JSON message and return all message fields"""
    try:
        if (data.get('from') == 'arduino'):
            t = data.get('to')
            d = data.get('distance')
            s = data.get('status')
            l = data.get('level')
    except ValueError:
        pass
    else:
        return (t, d, s, l)


def read_inputs():
    """Asks login credentials"""
    user = input('Username: ')
    pwd = getpass.getpass()
    return (user, pwd)
