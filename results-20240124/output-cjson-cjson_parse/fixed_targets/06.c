 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    char *string;
    struct cJSON *json;

    if(size <= 1) return 0;

    string = (char*)malloc(size);
    if(string == NULL) return 0;

    memcpy(string, data, size);

    json = cJSON_Parse(string);

    if(json != NULL) cJSON_Delete(json);

    free(string);

    return 0;
}

#ifdef __cplusplus
}
#endif