#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 100

int main () {
    int fd;
    char buf[BUF_SIZE];
    size_t len = sizeof(buf);
    ssize_t ret;
    fd = open("/Users/gimsehwan/Desktop/ingkle/2020-kpu-fall-embeded-system/system_code/test_file", O_RDONLY);

    while (len != 0 && (ret == read(fd, buf, len)) != 0) {
        if (ret == -1) {
            if (errno == EINTR)
            continue;
        perror("Read");
        break;
        }

        len += ret;
        buf += ret; //error occured
    }

    printf("this is buff \n");
    printf("%s",*buf);

    
    return 0;

}