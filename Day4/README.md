# 상호 배제와 병행성

## 1. 병행 프로세스의 개념

- 병행 프로세스 개념
    - 운영체제가 프로세서를 빠르게 전환
    - 프로세서 시간을 나눠 마치 프로세스 여러개를 동시에 실행하는 것 처럼 보이게 하는 것

- 병행 프로세스 종류
    - 독립 프로세스
        - 단일 처리 시스템에서 수행하는 병행 프로세스, 다른 프로세스에 영향 주고 받지 않으면서 독립 실행
        - 다른 프로세스, 데이터와 상태 공유 않고 동작도 재현 가능
        - 주어진 초기값에 따라 항상 동일한 결과
        - 중지 후 변동 없이 다시 시작 가능
        - 독립 실행 할 수 있는 프로세스
            - 단일 프로그래밍 : 프로세서를 사용 중이던 프로세스 완료 후 다른 프로세스 실행
            - 다중 프로그래밍 : 프로세스 여러 개가 프로세서 하나 공유, 공유하지 않는 상태 일 때 디스패치 순서 상관 없음
            - 다중 처리 : 프로세서 2개 이상 사용하여 동시에 프로그램 여러 개를 병렬 실행 프로세스는 한 번에 프로세서 하나에서 실행하지만, 동일한 시스템에서는 서로 다른 시간에 서로 다른 프로세서에서 실행 가능
    - 협력 프로세스 
        - 다른 프로세스와 상호작용하며 특정 기능 수행하는 비동기적 프로세스
        - 제한된 컴퓨터 자원의 효율성 증대, 계산 속도 향상, 모듈적 구성 강화, 개별 사용자의 여러 작업 동시에 수행 편의성 제공에 사용
        - 간단한 예 : 두 프로세스의 동일한 파일 사용시
        - 프로세스 하나가 파일에서 읽기 수행 동안 다른 프로세스가 해당 파일에 쓰기 수행하며 서로 영향
        - 병행 프로세스들이 입출력 장치, 메모리, 프로세서, 클럭 등 자원을 서로 사용시 충돌 발생
        - 충돌을 피하기 위한 프로세스의 상호작용 형태 
            1. 프로세스는 서로 인식하지 못하는 경쟁 관계 유지. 다중 프로그래밍 환경이 대표적인 예로, 운영체제가 자원 경쟁 고려하여 동일한 디스크나 프린터로 접근 조절
            2. 프로세스는 입출력 버스를 비롯한 개체를 공유하는 단계에서 간접적으로 서로 관계 인식. 이 때 다른 프로세스에서 얻은 정보에 의존, 프로세스의 타이밍에 영향. 프로세스들은 개체 공유에 따른 협력 필요
            3. 프로세스에는 서로 인식하고 프로세스끼리 통신할수있는 기본 함수 있음. 프로세스가 서로 협력관계에 있으면 직접 통신 가능, 병행해서 함께 동작 가능

## 2. 병행 프로세스의 해결 과제

- 병행성
    - 여러 프로세스를 이용하여 작업을 수행하는 것
    - 시스템 신뢰도 높이고 처리 속도 개선, 처리 능력 높이는 데 중요

- 병행 프로세스의 문제 
    - 공유 자원 상호 베타적 사용 (프린터, 통신망 등은 한 순간에 프로세스 하나만 사용)
    - 병행 프로세스 간의 협력이나 동기화
    - 두 프로세스 간 데이터 교환을 위한 통신
    - 동시에 수행하는 다른 프로세스의 실행 속도와 관계 없이 항상 일정한 실행 결과 보장(결정성 확보)
    - 교착 상태 해결, 병행 프로세스들의 병렬 처리 능력 극대화
    - 실행 검증 문제 해결
    - 병행 프로세스 수행 과정에서 발생하는 상호배제 보장

## 선형 그래프와 병행 프로그램

- 선행 그래프 (precedence graph)
    - 선행 제약의 논리적 표현
    - 프로세스 : 프로세스 집합과 이것의 선행 제약, 두가지 요소로 정의
    - 선행 제약 : 프로세스를 순서대로 다른 상태로 옮기는 것
        - 두 프로세스에 선행 제약이 없으면 이 둘은 독립적이므로 병행 실행 가능
    - 순차적 활동을 표현하는 방향성 비순환 그래프
    - 선행 그래프에서 노드는 소프트웨어 작업이거나 동시에 실행 할 수 있는 프로그램 명령

```python3

a = x + y # -> S1 S1과 S2는 동시 실행 가능
b = z + 1 # -> S2
c = a - b # -> S3 a, b 값이 할당 되기 전 수행 불가
w = c + 1 # -> S4 c 값 계산 전 수행 불가
```

![1](images/1.png) 

*비순환 선행 그래프와 선행 관계 예시*

- fork 와 join 구조
    - 선행 그래프는 연산의 선행 제약 정의에 유용하지만, 2차원이라 프로그램에는 사용 곤란
    - 선행 관계 명시 위해 fork와 join 구조, 병향 문장(parbegin, parend) 등 다른 방법 필요

![2](images/2.png)

*fork 구조의 알고리즘과 선행 그래프*


![3](images/3.png)

*join 구조의 알고리즘과 선행 그래프*

```text

간단한 산술 알고리즘

a := x + y;
b := z + 1;
c := a - b;
w := c + 1;

parbegin/parend 구조 알고리즘 
병행 처리 가능한건 하고, join 해서 한번에 처리

parbegin
    a := x + y;
    b := z + 1;
parend;
    c := a - b;
    w := c + 1;
```


```python3

from multiprocessing import Process, Queue

def work(id, start, end, result):
    total = 0
    for i in range(start, end):
        total += i
    result.put(total)
    return

if __name__ == "__main__":
    START, END = 0, 100000000
    result = Queue()
    th1 = Process(target=work, args=(1, START, END//2, result))
    th2 = Process(target=work, args=(2, END//2, END, result))
    
    th1.start()
    th2.start()
    th1.join()
    th2.join()

    result.put('STOP')
    total = 0
    while True:
        tmp = result.get()
        if tmp == 'STOP':
            break
        else:
            total += tmp
    print(f"Result: {total}")

```

*파이썬에서의 병렬처리 예*

위 멀티프로세싱 코드에서 보면. 

Queue 객체를 이용했는데, 이는 각각의 프로세스가 자신만의 메모리 공간을 사용 했기 때문에 프로세스간 데이터 교환을 위해 multiprocessing.Queue 객체를 이용해 데이터 교환을 한 것 .

```python3

th1.start()
th2.start()
th1.join()
th2.join()
```

join 을 사용한 이유는 메인 스레드 (메인 코드 블럭)가 th1, th2 각각의 프로세스가 작업을 종료 한 이후에 result.put('STOP') 과 같은 뒤에 오는 코드를 처리하도록 하기 위해서 계산하는 프로세스 끝날 때 까지 기다리라는 의미 !!!!!!

파이썬에서의 멀티 스레드와 멀티 프로세스의 차이라고 한다면 !!

멀티 스레딩은 가볍지만, GIL로 인해 계산하는 작업은 오직 하나의 스레드에서만 작업하기 때문에 여러 데이터를 동시에 계산하고, 단일 변수에 저장하고자 할 때는 불리하다. 다만 메모리를 각자 나누는게 아니기 때문에 메모리 이점은 있다.

멀티 프로세스는 프로세스 각자 고유한 메모리 영역을 할당받게 되기 때문에 메모리 측면에서는 불리하지만, 계산하는 작업을 빠르게 할 수 있다 !!

```python3
from multiprocessing import Process
import os

def info(title):
    print(title)
    print('module name:', __name__)
    print('parent process:', os.getppid())
    print('process id:', os.getpid())

def f(name):
    info('function f')
    print('hello', name)

if __name__ == '__main__':
    info('main line')
    p = Process(target=f, args=('bob',))
    p.start()
    p.join()
```

개별 프로세스의 ID를 보기 위해서 os 모듈을 import하고, getpid 호출 함.

- 파이썬 멀티프로세싱 모듈에서의 프로세스간 객체 교환

* 큐 

```python3
from multiprocessing import Process, Queue

def f(q):
    q.put([42, None, 'hello'])

if __name__ == '__main__':
    q = Queue()
    p = Process(target=f, args=(q,))
    p.start()
    print(q.get())    # prints "[42, None, 'hello']"
    p.join()
```

큐는 스레드와 프로세스에서 안전하다 !

* 파이프

```python3
from multiprocessing import Process, Pipe

def f(conn):
    conn.send([42, None, 'hello'])
    conn.close()

if __name__ == '__main__':
    parent_conn, child_conn = Pipe()
    p = Process(target=f, args=(child_conn,))
    p.start()
    print(parent_conn.recv())   # prints "[42, None, 'hello']"
    p.join()
```
Pipe() 가 반환하는 두개의 연결 객체는 파이프의 두 끝을 나타낸다.

- 프로세스 간 동기화
    - 멀티 프로세싱과 스레드 모두 한 번에 하나의 프로세스만 표준 출력을 인쇄하도록 Lock을 사용 할 수 있다 !

```python3

from multiprocessing import Process, Lock

def f(l, i):
    l.acquire()
    try:
        print('hello world', i)
    finally:
        l.release()

if __name__ == '__main__':
    lock = Lock()

    for num in range(10):
        Process(target=f, args=(lock, num)).start()

```

Lock을 사용하지 않으면 다른 프로세스의 출력이 모두 섞일 수도 있다.

* 프로세스간 상태 공유
    - 동시성 프로그래밍을 할 때 가능한 공유된 상태를 사용하지 않는 것이 최선이라고 함. 인터페이스는 존재

* 공유 메모리

```python3

from multiprocessing import Process, Value, Array

def f(n, a):
    n.value = 3.1415927
    for i in range(len(a)):
        a[i] = -a[i]

if __name__ == '__main__':
    num = Value('d', 0.0)
    arr = Array('i', range(10))

    p = Process(target=f, args=(num, arr))
    p.start()
    p.join()

    print(num.value)
    print(arr[:])
```


*더 간단한 예제 ㅠㅠ*

```python3

import threading
import time


class Worker(threading.Thread):
    def __init__(self, name):
        super().__init__()
        self.name = name            # thread 이름 지정

    def run(self):
        print("sub thread start ", threading.currentThread().getName())
        time.sleep(3)
        print("sub thread end ", threading.currentThread().getName())


print("main thread start")
for i in range(5):
    name = "thread {}".format(i)
    t = Worker(name)                # sub thread 생성
    t.start()                       # sub thread의 run 메서드를 호출

print("main thread end")

```

메인 스레드가 5개의 서브 스레드를 생성하고, start 메서드를 호출하여 Worker 클래스에서 정의한 run 메서드를 호출한다. 메인 스레드와 5 개의 서브 스레드는 운영체제의 스케줄러에 의해 스케줄링 되면서 실행 된다. 가장 먼저 메인 스레드가 끝나면서 main thread end를 출력한다.

위 코드의 출력

```console
(base)  ~/Desktop/ingkle/2020-kpu-fall-embeded-system/Day4   master  python3 mul.py                                                                               
main thread start
sub thread start  thread 0
sub thread start  thread 1
sub thread start  thread 2
sub thread start  thread 3
sub thread start  thread 4
main thread end
sub thread end  thread 0
sub thread end  thread 2
sub thread end  thread 4
sub thread end  thread 1
sub thread end  thread 3
```

만약 t.start() 밑에 t.join() 을 넣는다면 ? (해당 스레드가 종료되어야 메인스레드를 또 실행하는 함수니까, 각 스레드가 죽으면 넘어가고, 죽으면 넘어가고 하겠다)

```python3

import threading
import time


class Worker(threading.Thread):
    def __init__(self, name):
        super().__init__()
        self.name = name            # thread 이름 지정

    def run(self):
        print("sub thread start ", threading.currentThread().getName())
        time.sleep(3)
        print("sub thread end ", threading.currentThread().getName())


print("main thread start")
for i in range(5):
    name = "thread {}".format(i)
    t = Worker(name)                # sub thread 생성
    t.start()                       # sub thread의 run 메서드를 호출
    t.join() #각 스레드가 완료 될 때 까지 기다림

print("main thread end")

```


```console
(base)  ~/Desktop/ingkle/2020-kpu-fall-embeded-system/Day4   master  python3 mul.py
main thread start
sub thread start  thread 0
sub thread end  thread 0
sub thread start  thread 1
sub thread end  thread 1
sub thread start  thread 2
sub thread end  thread 2
sub thread start  thread 3
sub thread end  thread 3
sub thread start  thread 4
sub thread end  thread 4
main thread end
```

예상한 결과랑 동일하당!!!!

![4](images/4.png)

* Fork 랑 Join

지금 봅면 메인 스레드가 서브 스레드를 생성 하는걸 fork라고 한다.
그림처럼 2개의 서브 스레드를 생성한다면 총 3개의 스레드가 스케줄링 됩니다.  

join은 모든 스레드가 작업을 마칠 때 까지 기다리는 것인데, 보통 데이터를 여러 스레드가 병렬로 처리 하고, 그 값을 다시 모아서 순차적으로 처리 해야할 필요가 있을때 사용한다구 핝다 !!!!