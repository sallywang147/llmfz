#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  char *copy = (char *)malloc(size + 1);
  if (copy == NULL)
    return 0;

  memcpy(copy, data, size);
  copy[size] = '\0';

  cJSON *json = cJSON_Parse(copy);

  if (json != NULL)
    cJSON_Delete(json);

  free(copy);

  return 0;
}

#ifdef __cplusplus
}
#endif