#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s0[18] = "This is my test.X\0";
    char s1[16];
    char s2[16];
    strcpy(s1, s0);
    printf("s1: %s\ns2: %s\n", s1, s2);
    return 0;
}