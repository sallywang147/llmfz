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
    cJSON *object, *newitem, *replaced;
    char *string;
    size_t offset = 4;

    if(size <= offset) return 0;
    if(data[size-1] != '\0') return 0;
    if(data[0] != '1' && data[0] != '0') return 0;
    if(data[1] != '1' && data[1] != '0') return 0;
    if(data[2] != '1' && data[2] != '0') return 0;
    if(data[3] != '1' && data[3] != '0') return 0;

    object = cJSON_ParseWithOpts((const char*)data + offset, NULL, 0);

    if(object == NULL) return 0;

    string = (char*)malloc(size - offset);
    if(string == NULL) return 0;

    memcpy(string, data + offset, size - offset);

    newitem = cJSON_ParseWithOpts(string, NULL, 0);

    if(newitem == NULL) return 0;

    replaced = cJSON_ReplaceItemInObjectCaseSensitive(object, string, newitem);

    if(replaced == NULL) return 0;

    cJSON_Delete(object);
    cJSON_Delete(newitem);

    free(string);

    return 0;
}

#ifdef __cplusplus
}
#endif