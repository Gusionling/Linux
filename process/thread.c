#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_TRY 10000000

int shared = 0;

void *child_thread_main(void *arg)
{
    unsigned int i;
    printf("child pthread id %lu\n", pthread_self());
    
    for (i=0; i<MAX_TRY; i++){
        shared++;
    }
    for (i=0; i<MAX_TRY; i++){
        shared--;
    }
    
    return NULL;
}

int main(int argc, char **argv)
{
    int ret;
    pthread_t child_threads[2];
    
    printf("main pthread id %lu\n", pthread_self());
    ret = pthread_create(&child_threads[0], NULL, child_thread_main, NULL);
    if(ret){
        printf("pthread_create() fail(%d)\n", ret);
        return -1;
    }
    ret = pthread_create(&child_threads[1], NULL, child_thread_main, NULL);
    if(ret){
        printf("pthread_create() fail(%d)\n", ret);
        return -1;
    }
    
    printf("trying to join %lu\n", child_threads[0]);
    if(pthread_join(child_threads[0], NULL)){
        printf("pthread_join(%lu) fail\n", child_threads[0]);
    }
    printf("trying to join %lu\n", child_threads[1]);
    if(pthread_join(child_threads[1], NULL)){
        printf("pthread_join(%lu) fail\n", child_threads[1]);
    }
    
    printf("shared = %d\n", shared);
    printf("Done.\n");
    return 0;
}
