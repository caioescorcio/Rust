#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void parse(const char *input)
{
    // Goal: parse out a string between brackets
    // (e.g. "   [target string]" -> "target string")

    char *mutable_copy = strdup(input);
    int *key = malloc(sizeof(int));
    *key = input[0];

    // Find open bracket
    char *open_bracket = strchr(mutable_copy, '[');
    if (open_bracket == NULL)
    {
        printf("Malformed input!\n");
        free(mutable_copy);
        free(key);
        return;
    }

    // Make the output string start after the open bracket
    char *parsed = open_bracket + 1;

    // Make sure there is at least one character in brackets
    if (parsed[0] == '\0')
    {
        printf("There should be at least one character in brackets!\n");
        free(mutable_copy);
        free(key);
        return;
    }

    // Find the close bracket
    char *close_bracket = strchr(parsed, ']');
    if (close_bracket == NULL)
    {
        printf("Malformed input!\n");
        return;
    }

    // Replace the close bracket with a null terminator to end the parsed
    // string there
    *close_bracket = '\0';

    printf("Parsed string: %s (key: %d)\n", parsed, *key);
    free(mutable_copy);
    free(key);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <string to parse>\n", argv[0]);
        return 1;
    }

    parse(argv[1]);

    return 0;
}

/*
    4.a: The memory bug is in the close_bracket == NULL branch: mutable_copy and key are allocated but never freed before return,
    causing a memory leak. Clang-Tidy may warn about the leaked allocations, but static analysis can miss this depending on its
    enabled checks.

    LeakSanitizer should detect the leak when the program is given an input containing [ but no ], while AddressSanitizer/UBSan
    generally will not because there is no invalid memory access or undefined behavior. 4.b: A suitable input is [; strchr(mutable_copy, '[')
    succeeds, parsed points to the terminating '\0', so the function returns early after the “at least one character”
    check and actually frees both allocations—so this does not trigger the leak. Instead use [a: parsed[0] is non-null, strchr(parsed, ']')
    returns NULL, and the function returns without freeing either allocation. For example: ./bracket-parser "[a".

    LeakSanitizer should then report the leaked strdup() memory and malloc() memory. This demonstrates that dynamic analysis is input-dependent:
    sanitizers can detect a memory bug only when execution reaches the faulty code path, so passing tests or ordinary inputs do not prove the
    program is memory-safe.

*/
