#pragma once

typedef long (*lessthen)(const void*,const void*);
void quick_sort(void *data,int size,long num,lessthen);
long bsearch(void *data,void *target,int size,long num,lessthen);
