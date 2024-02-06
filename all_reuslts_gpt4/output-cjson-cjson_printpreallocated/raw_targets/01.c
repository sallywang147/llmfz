#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1)
    return 0;
  if (data[size - 1] != '\0')
    return 0;

  FuzzedDataProvider stream(data, size);
  int format = stream.ConsumeIntegralInRange(0, 1);
  std::string buffer = stream.ConsumeRemainingBytesAsString();

  cJSON *json = cJSON_Parse(buffer.c_str());
  if (json == NULL)
    return 0;

  char *preallocated_buffer = (char *)malloc(buffer.size());
  if (preallocated_buffer == NULL) {
    cJSON_Delete(json);
    return 0;
  }

  int result = cJSON_PrintPreallocated(json, preallocated_buffer, buffer.size(), format);

  free(preallocated_buffer);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif