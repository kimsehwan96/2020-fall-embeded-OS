# Vi

## 명령어 모드

## 비주얼 모드


```c
//main.c
#include <stdio.h>

void fn_print1();
void fn_print2();

int main() {
    printf("=====main====\n");
    fn_print1();
    fn_print2();

    return 0;
}
```

```c
//fn_print1()
#include <stdio.h>

void fn_print1() {
    printf("I am fn_print1\n");
}
```

```c
//fn_print2()
#include <stdio.h>

void fn_print2() {
    printf("I am fn_print2\n");
}

```

- 위 세개 파일을 컴파일하고 링크하는 방법

```bash
gcc -c main.c & gcc -c fn_print1.c & gcc -c fn_print2.c 

gcc -o my_print main.o fn_print1.o fn_print2.o

```

- gcc -o 옵션은 .o 목적파일들을 링크하여 실행파일 생성하는 것



## make

- 위 같이 컴파일하면 너무 귀찮으니 Makefile을 만들어서 사용.


```Makefile
OBJS = main.o fn_print1.o fn_print2.o

my_print : $(OBJS)
    gcc -o my_print $(OBJS)

main.o : main.c
    gcc -c main.c

fn_print1.o : fn_print1.c
    gcc -c fn_print1.c

fn_print2.o : fn_print2.c
    gcc -c fn_print2.c

clean :
    rm $(OBJS) my_print

```

`$ make`
`$ make clean`
