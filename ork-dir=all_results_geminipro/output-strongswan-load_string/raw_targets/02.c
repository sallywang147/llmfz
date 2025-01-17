#include <fuzzer/FuzzedDataProvider.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "private_settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use `c_str()` to use result as pointer
  std::string settings = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size));
  char *settings_ptr = settings.c_str();

  // Extract a boolean.
  bool merge = stream.ConsumeBool();

  // Consume the remaining bytes.
  std::vector<uint8_t> remaining_bytes = stream.ConsumeRemainingBytes();

  // Create a private_settings_t object.
  struct private_settings_t *this_ptr = new struct private_settings_t;
  assert(this_ptr != NULL);

  // Call the function to fuzz.
  bool result = load_string(this_ptr, settings_ptr, merge);

  // Free the private_settings_t object.
  delete this_ptr;

  return 0;
}