//현재 디렉터리 내의 파일과 서브 디렉터리에 대한 정보를 
//읽어와서 출력하는 프로그램이다. 주어진 디렉터리 내의 각 항목의 
//이름과 타입을 출력하는 목적을 가지고 있다. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

//이 메크로는 파일의 타입을 숫자 영태로 표현된 값에서 문자열로 변환하는 역할을 한다. 예를 들어 정수값 'DT_BLK'가 주어지면 "block device"로 변환된다. 코드내에서 switch문을 사용하지 않고 이러한 변환을 편리하게 수행할 수 있도록 도와준다. 

#define TYPE2STR(X) \
    ((X) ==  DT_BLK      ? "block device" :\
     (X) == DT_CHR        ? "char device" :\
     (X) ==  DT_DIR       ? "directory" :\
     (X) ==  DT_FIFO      ? "fifo" :\
     (X) ==  DT_LNK       ? "symlink" :\
     (X) ==  DT_REG       ? "regular file" :\
     (X) ==  DT_SOCK      ? "socket" :\
     "unknown")

 


int main(int argc, char **argv)
{
    DIR *dp;
    //dirent구조체는 디렉터리 항목을 나타낸다. 
    struct dirent *entry;

    //.하나는 현재 디렉터리를 의미한다.
    dp= opendir(".");
    if(!dp){
        printf("opendir() fail\n");
        return -1;
    }

    //while문이 있음으로써 파일이 있을 때까지만 받아오게 됨
    //readdir 함수를 사용하여 디렉터리에서 항목을 하나씩 읽어온다. 
    while((entry = readdir(dp))){
        printf("%s: %s\n",
                entry->d_name,
                TYPE2STR(entry->d_type)); 
    }

    closedir(dp);
    return 0;
}
