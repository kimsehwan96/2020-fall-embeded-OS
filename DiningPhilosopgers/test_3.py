import threading, queue, time

data = 0
lock = threading.Lock()
class Test(threading.Thread):
    def __init__(self, i):
        threading.Thread.__init__(self)
    def run(self):
        global data
        for _ in range(1, 10, 1):
            #lock.acquire()
            buf = data
            time.sleep(0.01)
            data = buf + 1
            #lock.release()
            print(threading.current_thread().getName(), data)


if __name__ == "__main__":
    meta = [Test(i) for i in range(5)]

    for t in meta:
        t.start()
#lock.acquire() & lock.release를 사용하기 전 아웃풋
'''
Thread-1 1
Thread-2 1
Thread-5 1
Thread-4 1
Thread-3 1
Thread-1 2
Thread-4 2
Thread-5 2
Thread-2 2
Thread-3 2
Thread-5 3
Thread-2 3
Thread-4 3
Thread-1 3
Thread-3 3
Thread-5 4
Thread-2 4
Thread-4 4
Thread-1 4
Thread-3 4
Thread-1 5
Thread-5 5
Thread-2 5
Thread-4 5
Thread-3 5
Thread-1 6
Thread-5 6
Thread-2 6
Thread-4 6
Thread-3 6
Thread-1 7
Thread-5 7
Thread-2 7
Thread-4 7
Thread-3 7
Thread-1 8
Thread-5 8
Thread-2 8
Thread-4 8
Thread-3 8
Thread-1 9
Thread-5 9
Thread-4 9
Thread-2 9
Thread-3 9
'''

#lock.acqure() & lock.release() 사용 후

#Thread-1 1
'''
Thread-2 2
Thread-3 3
Thread-4 4
Thread-5 5
Thread-1 6
Thread-2 7
Thread-3 8
Thread-4 9
Thread-5 10
Thread-1 11
Thread-2 12
Thread-3 13
Thread-4 14
Thread-5 15
Thread-1 16
Thread-2 17
Thread-3 18
Thread-3 19
Thread-5 20
Thread-1 21
Thread-2 22
Thread-4 23
Thread-3 24
Thread-5 25
Thread-1 26
Thread-2 27
Thread-4 28
Thread-3 29
Thread-5 30
Thread-1 31
Thread-2 32
Thread-4 33
Thread-3 34
Thread-5 35
Thread-1 36
Thread-2 37
Thread-4 38
Thread-3 39
Thread-5 40
Thread-1 41
Thread-2 42
Thread-4 43
Thread-5 44
Thread-4 45
'''