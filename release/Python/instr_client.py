# -*- coding: utf-8 -*-
"""
Program Name: instr_client.py                               
                                                     
Description : Instrument connector for https://instr.signalregistry.net

Author      : Hüseyin YİĞİT

E-Mail      : iletisim@huseyinyigit.com.tr

Version     : 0.0.1

"""
USER_ID = 'huseyin.yigit'

VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_PATCH = 1
version = '%d.%d.%d' % (VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH)

print(version)

import time
import websocket
import win32com.client
try:
    import thread
except ImportError:
    import _thread as thread




def on_message(ws, message):
    print(message)

def on_error(ws, error):
    print(error)

def on_close(ws):
    print("### closed ###")

def on_open(ws):
    def run(*args):
        for i in range(3):
            time.sleep(1)
            ws.send("Hello %d" % i)
        time.sleep(1)
        ws.close()
        print("thread terminating...")
    thread.start_new_thread(run, ())

if __name__ == "__main__":
    websocket.enableTrace(True)
    ws = websocket.WebSocketApp("ws://echo.websocket.org/",
                                on_message=on_message,
                                on_error=on_error,
                                on_close=on_close)
    ws.on_open = on_open
    ws.run_forever()