#include <string.h>
#include <malloc.h>
#include "fifo.h"
typedef long (*LT)(const void*,const void*);
long qs_partition(void *base,int size,long p1,long p2,LT lt)
{
    //p1,p2之间最小差２，这个由调用者检查
    char store[size];
    if(p1+2==p2){
        void *pp1=base + p1 * size;
        void *pp2=base + (p2-1)*size;
        if(lt(pp1,pp2)==0){
            memcpy(store,pp1,size);
            memcpy(pp1,pp2,size);
            memcpy(pp2,store,size);
        }
        return p1+1;
    }
    long store_idx=p1;
    void *povit=base+(p2-1)*size;
    void *pstore=base+store_idx * size;
    void *pix;
    while(1){
        if(lt(pstore,povit)){
            store_idx++;
            pstore+=size;
        }else{
            break;
        }
    }
    pix=base + store_idx * size;
    memcpy(store,pstore,size);
    for(long ix=store_idx+1;ix<p2-1;ix++){
        pix +=size;
        if(lt(pix,povit)){
            memcpy(pstore,pix,size);
            memcpy(pix,pstore,size);
            store_idx++;
        }
    }
    memcpy(pstore,povit,size);
    memcpy(povit,store,size);
    return store_idx;
}

int quick_sort(void *data,int size,long num,LT lt){
    FIFO bag=fifo_new(256);
    long val=num << 32;
    fifo_push(bag,(void *)val);
    while(1){
        if(fifo_pop(bag,(void **)&val)){
            return -1;
        }
        int p1=(int)val;
        int p2=(int)(val >> 32);
        long poidx=qs_partition(data,size,(long)p1,(long)p2,lt);
        int flag=0;
        if(poidx -p1 > 1){
            flag=1;
        }
        if(p2-poidx > 1){
            flag = flag | 0b10;
        }

    }
}
long bsearch(void *data,void *target,int size,long num,long (*lt)(const void*,const void*)){
    long start=0;
    long end=num;
    while(1){
        long mid;
        if(end-1==start){
            return start;
        }
        mid=(start+end)/2;
        void *ptr=data+mid*size;
        if(lt(target,ptr)){
            // 小于

        }
        
    }
    return 0;
}
