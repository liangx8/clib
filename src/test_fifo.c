#include <wchar.h>
#include <pthread.h>
#include <malloc.h>
#include <time.h>
#include "fifo.h"
#define CMAX 5
const struct timespec MS300={0,300000000};
const struct timespec MS30={0,30000000};
const struct timespec MS3={0,3000000};
struct {
    pthread_mutex_t *mutex;
    pthread_cond_t  *cond;
    FIFO fifo;
    int stop;
}td;
void* task(void *arg)
{
    int id=(int)(long)arg;
    void *data;
    pthread_mutex_lock(td.mutex);
    while(1){
        if(fifo_pop(td.fifo,&data)){
            // empty
            if(td.stop){
                break;
            }
            pthread_cond_wait(td.cond,td.mutex);
            continue;
        }
        pthread_mutex_unlock(td.mutex);
        wprintf(L"task %2d: %ld\n",id,(long)data);
        //nanosleep(&MS30,NULL);
        pthread_mutex_lock(td.mutex);
    }
    pthread_mutex_unlock(td.mutex);
    wprintf(L"%2d exit\n",id);
    return NULL;
}
int test_fifo(void)
{
    pthread_t pid[CMAX];
    pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
    td.mutex=&mutex;
    td.cond=&cond;
    td.stop=0;
    td.fifo=fifo_new(5);
    for(int ix=0;ix<CMAX;ix++){
        pthread_create(&pid[ix],NULL,task,(void*)(long)ix);
    }
    int bf=1;
    nanosleep(&MS300,NULL);
    for(int ix=0;ix<30;ix++){
        begin:
        pthread_mutex_lock(&mutex);
        if(fifo_push(td.fifo,(void*)(long)ix)){
            pthread_mutex_unlock(&mutex);
            if(bf){
                bf=0;
                wprintf(L"FIFO is full\n");
            }
            goto begin;
        }
        bf=1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        wprintf(L"\033[45mmain %d\033[0m\n",ix);
        //nanosleep(&MS300,NULL);
    }
    td.stop=1;
    pthread_cond_broadcast(td.cond);
    for(int ix=0;ix<CMAX;ix++){
        void *ret;
        pthread_join(pid[ix],&ret);
    }
    fifo_free(td.fifo);
    return 0;
}