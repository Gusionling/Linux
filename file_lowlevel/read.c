#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct person
{
    char name[16];
    int age;
};

static int write_info(struct person *p)
{
    int fd; 
    //signed size 
    ssize_t ret;

    fd = open("person_info", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if(fd == -1) {
        printf("open() fail\n");
        return -1;
    }
    ret = write(fd, p, sizeof(struct person));
    if(ret == -1){
        printf("write() fail\n");
        close(fd);
        return -1;
    } else if (ret != sizeof(struct person)) {
        printf("write() fail(partial write)\n");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

//파일을 읽어서 정보를 출력하는 함수 
static int dump_info(void)
{
    int fd; 
    //signed size 
    ssize_t ret;
    //buf를 위해서
    struct person p;


    //생성하는 것이 아니기에 권한도 필요하지 않다. 
    fd = open("person_info", O_RDONLY); 
    if(fd == -1) {
        printf("open() fail\n");
        return -1;
    }
    do{
        ret = read(fd, &p, sizeof(struct person));
        if(ret == -1){
            printf("read() fail\n");
            close(fd);
            return -1;
        }
        //EOF를 만났을 때 
        else if(ret == 0){
           //fdopen이 받아올 파일 포인터 
           FILE *fp;
           fp = fdopen(fd, "r");
           if(fp == NULL){
               printf("fdopen() fail\n");
               close(fd);
               return -1;
           }
           //현재 파일 포지션의 위피를 반환해줌 
           //ftell은 fopen계열의 api이다. 
           printf("file position = %ld\n" , ftell(fp));
           fclose(fp);
           break;
        }else if (ret != sizeof(struct person)) {
            printf("read() fail(partial read)\n");
            close(fd);
            return -1;
        }
        printf("name: %s, age: %d\n", p.name, p.age);
    }while(1); 
    close(fd);
    return 0;
}

int main(int argc, char **argv)
{
    //가변길이 배열
    struct person persons[] ={
        {"KIM", 30},
        {"LIM", 23}
    };

    write_info(&persons[0]);
    write_info(&persons[1]);
    
    dump_info();

    return 0;
}
