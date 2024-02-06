#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  if (size <= 4)
    return 0;
  if (data[size - 1] != '\0')
    return 0;
  if (data[0] != '1' && data[0] != '0')
    return 0;
  if (data[1] != '1' && data[1] != '0')
    return 0;

  int require_termination = data[0] == '1' ? 1 : 0;
  int format = data[1] == '1' ? 1 : 0;
  
  cJSON *json = cJSON_ParseWithOpts((const char *)data + 2, NULL, require_termination);
  if (json == NULL)
    return 0;

  int length = stream.ConsumeIntegralInRange<int>(0, size);
  char* buffer = (char*) malloc(length * sizeof(char));
  if (buffer == NULL)
    return 0;

  cJSON_PrintPreallocated(json, buffer, length, format);

  free(buffer);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif