#! /usr/env/python3

#식사하는 철학자 데드락 구현

import sys
import threading
import time

class Fork:

    def __init__(self, number):
        #총 5개의 젓가락, 각자 고유한 넘버 가진다
        self.number = number
        self.user = -1
        self.lock = threading.Condition(threading.Lock()) #공유자원 락
        self.taken = False # 처음에는 모든 젓가락이 내려감
    
    def take(self, user):
        with self.lock:
            while self.taken == True:
                self.lock.wait() #들고있을때 자원 잠궈놓음(다른 스레드에서 접근 불가)
            self.user = user
            self.taken = True
            print("{} took {} fork".format(user, self.number))
            self.lock.notifyAll()

    def drop(self, user):
        with self.lock:
            while self.taken == False:
                self.lock.wait()
            self.user = -1
            self.taken = False
            print("{} dropped {} fork".format(user, self.number))
            self.lock.notifyAll()

class Philosopher(threading.Thread):

    def __init__(self, number, left, right):
        threading.Thread.__init__(self)
        self.number = number
        self.left = left
        self.right = right
    
    def run(self):
        for i in range(20):
            time.sleep(0.1) # 생각하기
            self.left.take(self.number) #왼쪽 젓가락 들기
            time.sleep(0.1)
            self.right.take(self.number) #오른쪽 젓가락 들기
            time.sleep(0.1)
            self.right.drop(self.number) #식사 후 오른쪽 젓가락 내리기
            self.left.drop(self.number) # 식사후 왼쪽 젓가락 내리기
            
        print(" {} phliosopher finished eating ".format(self.number))

if __name__ == "__main__":
    n = 5
    f = [Fork(i) for i in range(5)]

    p = [Philosopher(i, f[i], f[(i+1)%n]) for i in range(5)]

    for i in range(n):
        p[i].start()
    #데드락에 걸려버림 ㅎㅎ  