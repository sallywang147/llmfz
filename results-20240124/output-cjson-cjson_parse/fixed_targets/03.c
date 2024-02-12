 #include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    char *string = (char*)malloc(size + 1);
    memcpy(string, data, size);
    string[size] = 0;

    cJSON_Parse(string);

    free(string);

    return 0;
}

#ifdef __cplusplus
}
#endif