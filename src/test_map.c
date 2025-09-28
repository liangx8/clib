#include <wchar.h>
#include <malloc.h>
#include "map.h"
const wchar_t *str1=L"一开始就开漏拉恶";
const wchar_t *const names[5]={L"one line",L"二看看电视库垃圾堆",L"three line",L"four line",L"5行"};
int test_map(void)
{
    MAP map=map_new(10);
    map_set(map,4,names[4]);
    map_set(map,1,names[1]);
    map_set(map,3,names[3]);
    map_set(map,0,names[0]);
    map_set(map,2,names[2]);
    for(int ix=4;ix>=0;ix--){
        const wchar_t *str;
        if(map_get(map,ix,(void **)&str)){
            wprintf(L"get error\n");
            map_free(map);
            return -1;
        }
        wprintf(L"key:%d value:%ls\n",ix,str);
    }
    map_free(map);
    return 0;
}