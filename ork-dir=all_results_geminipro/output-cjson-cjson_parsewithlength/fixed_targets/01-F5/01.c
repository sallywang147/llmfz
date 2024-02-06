#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

extern "C" LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  cJSON *json;
  unsigned char *copied;

  if (size <= 1)
    return 0;
  if (data[size - 1] != '\0')
    return 0;

  copied = (unsigned char *)malloc(size);
  if (copied == NULL)
    return 0;

  memcpy(copied, data, size);

  json = cJSON_ParseWithLength((char *)copied, size - 1);

  if (json == NULL)
    return 0;

  cJSON_Delete(json);

  free(copied);

  return 0;
}

#ifdef __cplusplus
}
#endif