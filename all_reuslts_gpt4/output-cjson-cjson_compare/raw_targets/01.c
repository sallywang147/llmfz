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
  
  // Consume half the size for each cJSON object
  size_t half_size = size / 2;
  
  std::string str1 = stream.ConsumeBytesAsString(half_size);
  std::string str2 = stream.ConsumeRemainingBytesAsString();
  
  cJSON *json1 = cJSON_Parse(str1.c_str());
  cJSON *json2 = cJSON_Parse(str2.c_str());
  
  if (json1 == NULL || json2 == NULL) {
    if (json1 != NULL) {
      cJSON_Delete(json1);
    }
    if (json2 != NULL) {
      cJSON_Delete(json2);
    }
    return 0;
  }
  
  int case_sensitive = stream.ConsumeBool();
  
  cJSON_Compare(json1, json2, case_sensitive);
  
  cJSON_Delete(json1);
  cJSON_Delete(json2);
  
  return 0;
}

#ifdef __cplusplus
}
#endif