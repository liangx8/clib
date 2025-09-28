#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include "bfind.h"
#define MAX 10
//typedef long (*lessthen)(const void*,const void*);

int datalt(const unsigned *l,const unsigned *r)
{
    if(*l<*r){
        return -1;
    }
    if(*l>*r){
        return 1;
    }
    return 0;
}
void disp(int data[])
{
    for(int ix=0;ix<MAX;ix++){
        wprintf(L"%2d: %10u,%3d\n",ix,data[ix*2],data[ix*2+1]);
    }
}
int les(const unsigned *l,const unsigned *r)
{
    return *l<*r;
}
int test_sort(void){
    int data[MAX*2];
    FILE *rnd=fopen("/dev/random","r");
    for(int ix=0;ix<MAX;ix++){
        fread(&data[ix*2],1,4,rnd);
        data[ix*2] &= 0xffff;
        data[ix*2+1]=ix;
    }
    fclose(rnd);
    qsort(data,MAX,8,(int (*)(const void *,const void*)) datalt);
    disp(data);
    int num=data[5*2];
    long res=bfind(data,&num,8,MAX,(LT)les);
    wprintf(L"find %5d,结果:%2d\n",num,res);
    num=2000;
    res=bfind(data,&num,8,MAX,(LT)les);
    wprintf(L"find %5d,结果:%2d\n",num,res);
    num=70000;
    res=bfind(data,&num,8,MAX,(LT)les);
    wprintf(L"find %5d,结果:%2d\n",num,res);
    return 0;
}