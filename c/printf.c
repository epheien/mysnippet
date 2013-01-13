#include <stdio.h>

/* 同时一直刷新数行 */

int main(void)
{
    int i = 0;
    while (1) {
        printf("%d\n", i);
        printf("%d\n", i);
        printf("%d\n", i);
        printf("%d\n", i);
        printf("\033[4A");
        printf("\033[K");
        i++;
        sleep(1);
    }
    return 0;
}
