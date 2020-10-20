#! /usr/env/python3

import threading

def test():
    for i in range(1, 100, 1):
        print(i)


for i in range(5):
    threading.Thread(target=test()).start()
