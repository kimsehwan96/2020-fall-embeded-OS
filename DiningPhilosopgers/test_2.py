import threading, queue, time

i = 0

class Test(threading.Thread):
    def __init__(self, i):
        threading.Thread.__init__(self)
    def run(self):
        global i
        for _ in range(10):
            i += 1
            print(threading.current_thread().getName(), i)


if __name__ == "__main__":
    meta = [Test(i) for i in range(5)]

    for t in meta:
        t.start()
#다른 스레드가 끝나기도 전에 호출되었다.
'''
Thread-1 1 #
Thread-1 3 #
Thread-2 2 # 스레드가 동시에 동시에 실행되면서, 동기화가 되지 않음.
Thread-1 4
Thread-2 6
Thread-4 7
Thread-4 11
Thread-2 10
Thread-5 9
Thread-4 12
Thread-4 15
Thread-4 16
Thread-1 8
Thread-3 5
Thread-5 14
Thread-1 17
Thread-4 21
Thread-5 19
Thread-1 20
Thread-4 22
Thread-1 23
Thread-1 26
Thread-4 24
Thread-5 25
Thread-1 28
Thread-2 13
Thread-5 27
Thread-5 30
Thread-5 31
Thread-3 18
Thread-2 34
Thread-1 29
Thread-4 35
Thread-4 36
Thread-3 33
Thread-3 37
Thread-2 38
Thread-3 39
Thread-2 40
Thread-5 32
Thread-3 41
Thread-2 42
Thread-3 44
Thread-5 43
Thread-3 47
Thread-3 48
Thread-3 49
Thread-5 46
Thread-2 45
Thread-2 50
'''
