#include <stdint.h>
#include <stddef.h>

void parse(const char *input);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    char input[size + 1];

    for (size_t i = 0; i < size; i++)
        input[i] = (char)data[i];

    input[size] = '\0';

    parse(input);
    return 0;
}