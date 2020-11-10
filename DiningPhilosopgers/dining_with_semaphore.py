#! /usr/env/python3

#식사하는 철학자 데드락 구현

import sys
import threading
import time

#user : 0, 1, 2, 3, 4
#Fork : 0, 1, 2, 3, 4 
#           0
#       1       4
#         2   3


class Semaphore:
    def __init__(self, initial):
        self.lock = threading.Condition(threading.Lock())
        self.value = initial
    
    def up(self):
        with self.lock:
            self.value += 1
            self.lock.notify()

    def down(self):
        with self.lock:
            while self.value == 0:
                self.lock.wait()
            self.value -= 1

class Fork:
    def __init__(self, number):
        #총 5개의 젓가락, 각자 고유한 넘버 가진다
        self.number = number
        self.user = -1 #user = -1 일경우 그 누구의 소유도 아님
        self.lock = threading.Condition(threading.Lock()) #공유자원 락
        self.taken = False # 처음에는 모든 젓가락이 내려감
    
    def take(self, user):
        with self.lock:
            while self.taken == True:
                self.lock.wait() #락을 해제한당
            self.user = user
            self.taken = True # 젓가락 든상태 
            print("{} took {} fork".format(user, self.number))
            self.lock.notifyAll() # 다른 스레드가 호출해서 해제하기 전까지 블록(막아둠)

    def drop(self, user):
        with self.lock:
            while self.taken == False:
                self.lock.wait()
            self.user = -1
            print("this is dropped user {}".format(self.user))
            self.taken = False
            print("{} dropped {} fork".format(user, self.number))
            self.lock.notifyAll()

class Philosopher(threading.Thread): #철학자 객체 -> 스레드

    def __init__(self, number, left, right ,butler):
        threading.Thread.__init__(self) #각 철학자는 하나의 스레드다 
        self.number = number #철학자 고유 id 
        self.left = left #왼쪽
        self.right = right #오른쪽
        self.butler = butler
    
    def run(self):
        for i in range(20):
            self.butler.down()
            time.sleep(0.1) # 생각하기
            self.left.take(self.number) #왼쪽 젓가락 들기
            time.sleep(0.1)
            self.right.take(self.number) #오른쪽 젓가락 들기
            time.sleep(0.1)
            self.right.drop(self.number) #식사 후 오른쪽 젓가락 내리기
            self.left.drop(self.number) # 식사후 왼쪽 젓가락 내리기
            self.butler.up()            
        print(" {} phliosopher finished eating ".format(self.number))

if __name__ == "__main__":
    n = 5
    
    butler = Semaphore(n-1)

    f = [Fork(i) for i in range(5)]

    p = [Philosopher(i, f[i], f[(i+1) % n],  butler) for i in range(5)]
    # i + 1 % n 의 이유 -> i = 4 , 5 = 5일경우, 0으로 바꿔주기 위해서 (원형)

    for i in range(n):
        p[i].start() # 각 철학자 스레드 실행 시작 ~!
