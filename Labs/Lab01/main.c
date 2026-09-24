// void function(int a, int b, int c)
// {
//     char buffer1[5];
//     char buffer2[10];
// }
// int main()
// {
//     function(1, 2, 3);
//     return 0;
// }

#include <string.h>

void function(char *str)
{
    char buffer[16];
    strcpy(buffer, str);
}

int main()
{
    char large_string[256];
    int i;

    for (i = 0; i < 255; i++)
    {
        large_string[i] = 'A';
    }
    function(large_string);

    return 0;
}
