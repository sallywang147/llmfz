#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  cJSON *json;

  if (size <= 1)
    return 0;
  if (data[size - 1] != '\0')
    return 0;

  json = cJSON_ParseWithLength((char *)data, size - 1);

  if (json == NULL)
    return 0;

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif