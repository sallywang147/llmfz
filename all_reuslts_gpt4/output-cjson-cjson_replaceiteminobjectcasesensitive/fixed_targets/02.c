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
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  cJSON *root = cJSON_CreateObject();
  if (root == NULL) {
    return 0;
  }

  std::string key = stream.ConsumeRandomLengthString();
  cJSON *value = cJSON_CreateString(key.c_str());
  if (value == NULL) {
    cJSON_Delete(root);
    return 0;
  }

  cJSON_AddItemToObject(root, key.c_str(), value);

  std::string replaceKey = stream.ConsumeRandomLengthString();
  cJSON *replaceValue = cJSON_CreateString(replaceKey.c_str());
  if (replaceValue == NULL) {
    cJSON_Delete(root);
    return 0;
  }

  cJSON_ReplaceItemInObjectCaseSensitive(root, (char*)replaceKey.c_str(), replaceValue);

  cJSON_Delete(root);

  return 0;
}

#ifdef __cplusplus
}
#endif