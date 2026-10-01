#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void my_strcpy(char *dest, const char *src)
{
    size_t i = 0;
    while (true)
    {
        dest[i] = src[i];
        if (src[i] == '\0')
        {
            break;
        }
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <string to uppercase>\n", argv[0]);
        return 1;
    }

    char uppercase[strlen(argv[1])];

    /*
        he bug is char uppercase[strlen(argv[1])];: strlen() excludes the terminating '\0',
        but my_strcpy() copies it, causing a one-byte stack buffer overflow and undefined behavior;
        fix it with char uppercase[strlen(argv[1]) + 1]; so there is room for the null terminator.
    */

    /*
    The normal executable is 18,040 bytes, while the sanitized versions are much larger:
    AddressSanitizer (uppercase_a) is 1,646,376 bytes (~91× larger), LeakSanitizer (uppercase_l) is
     462,216 bytes (~26× larger), and the other sanitizer build (uppercase_s) is 415,256 bytes (~23× larger);

     this happens because sanitizers add instrumentation and runtime support code to detect memory errors and undefined
     behavior during execution.

    $ ./uppercase "a"
    A

    $ ./uppercase_s "a"
    uppercase.c:38:21: runtime error: index 1 out of bounds for type 'char[strlen(argv[1])]'
    SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior uppercase.c:38:21
    A

    $ ./uppercase_l "a"
    A

    $ ./uppercase_s "a"
    uppercase.c:38:21: runtime error: index 1 out of bounds for type 'char[strlen(argv[1])]'
    SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior uppercase.c:38:21
    A
    */

    my_strcpy(uppercase, argv[1]);

    for (int i = 0; uppercase[i] != '\0'; i++)
    {
        if (uppercase[i] >= 'a' && uppercase[i] <= 'z')
        {
            uppercase[i] = uppercase[i] - ('a' - 'A');
        }
    }

    printf("%s\n", uppercase);
}
