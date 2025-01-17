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
    struct cJSON *json;
    char *copied;

    if(size <= 1) return 0;

    copied = (char*)malloc(size);
    if(copied == NULL) return 0;

    memcpy(copied, data, size);

    json = cJSON_Parse(copied);

    if(json != NULL) cJSON_Delete(json);

    free(copied);

    return 0;
}

#ifdef __cplusplus
}
#endif