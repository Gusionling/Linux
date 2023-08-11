#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc,  char **argv)
{
    int ret;
    int flag;
    char buf[128];
    int fd;

    fd = STDIN_FILENO;
    
    printf("trying to read...\n");
    memset(buf, 0, sizeof(buf));
    //STDIN은 기본적으로 blocking mode이다. 
    ret = read(fd,  buf, sizeof(buf));
    printf("read() [%s] - %d bytes\n", buf, ret);
    //STDIN은 fd를 자동을 닫아준다. 

    
    flag = fcntl(fd, F_GETFL);
    if(flag == -1){
        printf("fcntl(F_GETFL) fail\n");
        return -1;
    }
    
    //STDIN_FILNO를 O_NONBLOCK 으로 바꿔주면 얘는 그걸 기억하고 있어서
    //CMD창을 한번 닫았다가 다시 실행해야함
    ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
    if(ret == -1) {
        printf("fcntl(F_SETFL) fail\n");
        return -1;
    }
   
    printf("trying to read...\n"); 
    memset(buf, 0, sizeof(buf));
    ret = read(fd,  buf, sizeof(buf));
    printf("read() [%s] - %d bytes\n", buf, ret);
    if(ret == -1){
        printf("errno = %d, %s\n", errno, strerror(errno));
    }

    return 0;
}
