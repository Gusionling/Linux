#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>


int main(int argc, char **argv)
{
    int fd = -1;
    int wd1 = -1;
    int wd2 = -1;
    char buf[1024];
    int ret;
    struct inotify_event *event;

    fd = inotify_init();
    if(fd == -1){
        printf("inotify_init() fail\n");
        return -1;
    }

    wd1 = inotify_add_watch(fd, ".", IN_CREATE | IN_DELETE);
    if(wd1 == -1){
        printf("add_watch() fail\n");
        goto err;
    }
    wd2 = inotify_add_watch(fd, "../file_basic", IN_CREATE | IN_DELETE);
    if(wd2 == -1){
        printf("add_watch() fail\n");
        goto err;
    }
    while(1) {
        ret = read(fd, buf, sizeof(buf));
        if(ret == -1){
            printf("read() fail\n");
            break;
        }

        event = (struct inotify_event *)&buf[0];
        while(ret>0){
            if(event->mask & IN_CREATE){
                printf("file %s is created\n", event->name);
            }
            if(event->mask & IN_DELETE){
                printf("file %s is deleted\n", event->name);
            }
            //다음 이벤트가 있는 위치 
            event =(struct inotify_event *)((char *)event + sizeof(struct inotify_event) + event->len);
            ret -= (sizeof(struct inotify_event) + event->len);
        }
    }
    close(wd1);
    close(wd2);
    close(fd);

    return 0;

err:
    if( fd >=0){
        close(fd);
    }
    if(wd1>=0){
        close(wd1);
    }
    if(wd2>=0){
        close(wd2);
    }
    return -1;
}

