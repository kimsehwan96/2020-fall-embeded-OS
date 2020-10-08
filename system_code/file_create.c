#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

// filename 으로 파일을 만드는 코드. creat 시스템 콜 이용.
//create 이 아닌것에 주의하기.

int main() {
    int fd;
    char *filename = "test_file";
    //fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); //아래 코드와 동일하다고 한다.
    fd = creat(filename, 0644);
    if (fd == -1) {
        printf("this is error");
    }
    else{
        printf("create file!\n");
        printf("this is fd number %d", fd); //fd = 3
    }

    return 0;
}