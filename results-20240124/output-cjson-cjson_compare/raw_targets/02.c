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
    cJSON *json1;
    cJSON *json2;
    size_t offset = 4;
    unsigned char *copied;
    char *printed_json = NULL;
    int minify, require_termination, formatted, buffered;


    if(size <= offset) return 0;
    if(data[size-1] != '\0') return 0;
    if(data[0] != '1' && data[0] != '0') return 0;
    if(data[1] != '1' && data[1] != '0') return 0;
    if(data[2] != '1' && data[2] != '0') return 0;
    if(data[3] != '1' && data[3] != '0') return 0;

    minify              = data[0] == '1' ? 1 : 0;
    require_termination = data[1] == '1' ? 1 : 0;
    formatted           = data[2] == '1' ? 1 : 0;
    buffered            = data[3] == '1' ? 1 : 0;

    json1 = cJSON_ParseWithOpts((const char*)data + offset, NULL, require_termination);

    if(json1 == NULL) return 0;

    json2 = cJSON_ParseWithOpts((const char*)data + offset, NULL, require_termination);

    if(json2 == NULL) return 0;

    cJSON_Compare(json1, json2, 0);

    cJSON_Delete(json1);
    cJSON_Delete(json2);

    return 0;
}

#ifdef __cplusplus
}
#endif