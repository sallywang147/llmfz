#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *ptr = const_cast<char *>(str.c_str());

  cJSON *json = cJSON_Parse(ptr);

  if (json != NULL)
    cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif