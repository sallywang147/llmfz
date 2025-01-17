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
  
  std::string str = stream.ConsumeRandomLengthString();
  char *value = str.c_str();

  struct cJSON *json = cJSON_ParseWithLength(value, size);

  if (json != NULL) {
    cJSON_Delete(json);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif