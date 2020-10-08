#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main () {
    int fd;

    fd = open("/Users/gimsehwan/Desktop/ingkle/2020-kpu-fall-embeded-system/system_code/perror_test.c", O_RDONLY);

    if (fd == -1){ // 파일디스크립터는 양수값만으로 존재
        printf("this is error");
    }
    else {
        printf("this is fd number %u", fd); // fd = 3 리턴 받음. 파일디스크립터는 음수가 허용되지 않음.
    }
    
    return 0;

}