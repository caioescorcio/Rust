// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char s0[1] = "-";
//     char s2[8] = "secret";
//     char s1[8] = "00000000";
//     strcat(s0, s1);
//     printf("s0: %s\n", s0);
//     return 0;
// }

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *foo(void);

int main(void)
{
    char s0[32] = "-";

    char *p = foo();

    strcat(s0, p);

    printf("s0: %s\n", s0);

    return 0;
}

char *foo(void)
{
    static struct
    {
        char s2[16];
        char s3[8];
    } x = {
        "0123456789ABCDEF", // exactly 16 chars, no '\0'
        "secret"};

    return x.s2;
}