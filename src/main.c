#include <wchar.h>
#include <locale.h>

int test_fifo(void);
int test_sort(void);
int test_map(void);
int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    test_fifo();
    test_sort();
    test_map();
}