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

  // We need at least 3 bytes to proceed: 1 for case_sensitive and 2 for JSON strings
  if (size < 3) {
    return 0;
  }

  // Consume first byte as case_sensitive flag
  int case_sensitive = stream.ConsumeIntegralInRange(0, 1);

  // Split the remaining data into two parts
  size_t remaining_size = size - 1;
  size_t first_size = remaining_size / 2;
  size_t second_size = remaining_size - first_size;

  // Consume first part as JSON string for 'a'
  std::string a_str = stream.ConsumeBytesAsString(first_size);
  cJSON *a = cJSON_Parse(a_str.c_str());
  if (a == NULL) {
    return 0;
  }

  // Consume second part as JSON string for 'b'
  std::string b_str = stream.ConsumeRemainingBytesAsString();
  cJSON *b = cJSON_Parse(b_str.c_str());
  if (b == NULL) {
    cJSON_Delete(a);
    return 0;
  }

  // Call the target function
  cJSON_Compare(a, b, case_sensitive);

  // Cleanup
  cJSON_Delete(a);
  cJSON_Delete(b);

  return 0;
}

#ifdef __cplusplus
}
#endif