#include <fuzzer/FuzzedDataProvider.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "private_settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a private_settings_t struct.
  struct private_settings_t *this_ptr = new struct private_settings_t;
  memset(this_ptr, 0, sizeof(struct private_settings_t));

  // Generate random values for the struct members.
  this_ptr->settings = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange(0, 1024)).c_str();
  this_ptr->merge = provider.ConsumeBool();
  this_ptr->key = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange(0, 1024)).c_str();

  // Call the function to be fuzzed.
  bool result = load_string_section(this_ptr, this_ptr->settings, this_ptr->merge, this_ptr->key);

  // Clean up the allocated memory.
  delete this_ptr;

  return 0;
}