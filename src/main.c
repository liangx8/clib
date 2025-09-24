#include <wchar.h>
#include <locale.h>

int test_fifo(void);
int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    test_fifo();
}