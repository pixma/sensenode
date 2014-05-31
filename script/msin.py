import os
import serial, time
from serial.tools import list_ports
import xively
import re
import datetime
from time import sleep

XIVELY_API_KEY = "qjGVzi8d3knhWq1rhygjf3TZDsq4irvfZdmlwrsAlNbBWf4a"
XIVELY_FEED_ID = 2144897203

def serial_ports():
    """
    Returns a generator for all available serial ports
    """
    if os.name == 'nt':
        # windows
        for i in range(256):
            try:
                s = serial.Serial(i)
                s.close()
                yield 'COM' + str(i + 1)
            except serial.SerialException:
                pass
    else:
        # unix
        for port in list_ports.comports():
            yield port[0]


if __name__ == '__main__':
    comList = list(serial_ports())
    validComLocation = comList[len(comList) - 1]
    ser = serial.Serial()
    ser.port = validComLocation
    ser.baudrate = 9600
    ser.bytesize = serial.EIGHTBITS
    ser.parity = serial.PARITY_NONE
    ser.stopbits = serial.STOPBITS_ONE
    ser.timeout = None
    ser.xonxoff = False     #disable software flow control
    ser.rtscts = False     #disable hardware (RTS/CTS) flow control
    ser.dsrdtr = False       #disable hardware (DSR/DTR) flow control
    ser.writeTimeout = 2     #timeout for write
    ser.open()

    api = xively.XivelyAPIClient(XIVELY_API_KEY)
    feed = api.feeds.get(XIVELY_FEED_ID)
    now = datetime.datetime.utcnow()
    
    if ser.isOpen():
        while True:
            try:
                response = ser.readline()
                responseString = str(response, 'utf8')
                print(responseString)
                research = re.search('([0-9]+),([0-9]+)', responseString)
                print(research.group())
                print(research.group(1))
                print(research.group(2))

                feed.datastreams = [
                   xively.Datastream(id=research.group(2), current_value=research.group(1), at=now)
                ]
                feed.update()
                sleep(10)
                
            except Exception as e:
                print(e)


