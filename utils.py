import builtins
import getpass
import serial
import queue
from colored import fore, style
from serial.tools import list_ports
from serial.threaded import LineReader

REMOTE = 'remote'
ARDUINO = 'arduino'
LOCAL = 'local'


class PrintLines(LineReader):
    def connection_made(self, transport):
        super(PrintLines, self).connection_made(transport)
        self.daemon = True
        self.from_arduino = queue.Queue()

    def handle_line(self, data):
        try:
            from simplejson import loads
            loads(data)
        except ValueError:
            pass
        else:
            self.from_arduino.put(data)

    def get_message_queue(self):
        return self.from_arduino

    def connection_lost(self, exc):
        print('Port Closed!', 1)


def print(msg, t=0):
    if t == 0:
        builtins.print(fore.BLUE + style.BOLD + msg + style.RESET)
    if t == 1:
        builtins.print(fore.RED + style.BOLD + msg + style.RESET)


def connect_arduino():
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
        arduino.setDTR(False)
        import time
        time.sleep(.022)
        arduino.flushInput()
        arduino.flushOutput()
        arduino.setDTR(True)
        return arduino


def parse_json(data):
    try:
        from simplejson import loads
        data = loads(data)
        msg = data.get('msg')
        f = data.get('from')
        t = data.get('to')
    except ValueError:
        pass
    else:
        return (msg, f, t)


def read_inputs():
    user = input('Username: ')
    pwd = getpass.getpass()
    return (user, pwd)
