#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <errno.h>

static void print_usage(const char *progname)
{
    printf("usage: %s (ex|sh)\n", progname);
    exit(-1);
}

int main(int argc, char **argv)
{
    int fd;
    int ops;

    //실행하는 파일 이름이 첫번째 파라미터가 된다. 
    if(argc <2){
        print_usage(argv[0]);
    }

    fd = open("lockfile", O_RDWR | O_CREAT, 0644);
    if(fd<0){
        printf("open() fail\n");
        return -1;
    }
    if(!strcmp(argv[1], "sh")){
        ops = LOCK_SH;
    }else if(!strcmp(argv[1], "ex")){
        ops = LOCK_EX;
    }else{
        print_usage(argv[0]);
    }
    
    //lock을 잡고
    printf("trying to grab the lock\n");
    if(flock(fd, ops) != 0){
        printf("flock(ops %d), errno=%d(%s)\n", ops, errno, strerror(errno));
        goto out;
    }
        
    //잠시 사용자의 입력을 기다렸다가 
    printf("grab the lock!!\n");
    getc(stdin);
    //lock을 푼다
    if(flock(fd, LOCK_UN)){
        printf("flock(unlock)\n");
        goto out;
    }


    return 0;

out:
    close(fd);
    return -1;
}
