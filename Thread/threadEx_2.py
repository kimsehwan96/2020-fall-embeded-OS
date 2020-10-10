from threading import Thread, active_count, get_ident

def work_1():
    count = 0
    for i in range(100): 
        count += 1
        print("this is thread ! & count here {}".count)
        print("active thread count {}".format(active_count()))
        print("I'am thread 1")

def work_2():
    count = 0
    for i in range(100): #100000 회 반복
        count += 1
        print("this is thread ! & count here {}".count)
        print("active thread count {}".format(active_count()))
        print("I'am thread 2")



if __name__ == "__main__":
    th1 = Thread(target=work_1)
    th2 = Thread(target=work_2)
    
    th1.start()
    th2.start()
    th1.join()
    th2.join()