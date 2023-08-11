#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

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
    struct dirent *entry;

    //.하나는 현재 디렉터리를 의미한다.
    dp= opendir(".");
    if(!dp){
        printf("opendir() fail\n");
        return -1;
    }

    //while문이 있음으로써 파일이 있을 때까지만 받아오게 됨
    while((entry = readdir(dp))){
        printf("%s: %s\n",
                entry->d_name,
                TYPE2STR(entry->d_type)); 
    }

    closedir(dp);
    return 0;
}
