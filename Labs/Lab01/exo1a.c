#include <stdlib.h>
#include <stdio.h>

char buf2[8];

int main(void)
{
    char *buf1 = malloc(8);
    char buf3[8];
    for (int i = 0; i < 100; i++)
    {
        buf1[i] = 'A'; // CWE-787: eventually writes past the allocation
        printf("%c", buf1[i]);
    }

    printf("\n");
    for (int i = 0; i < 100; i++)
    {
        buf2[i] = 'A';
        printf("%c", buf2[i]);
    }

    printf("\n");
    for (int i = 0; i < 100; i++)
    {
        buf3[i] = 'A';
        printf("%c", buf3[i]);
    }

    printf("\n");
    free(buf1);
    return 0;
}