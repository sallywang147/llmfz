#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract a string. 
  std::string settings_str = stream.ConsumeRemainingBytesAsString();
  
  // Call the function with the fuzzed input
  struct settings_t* settings = settings_create_string(settings_str.c_str());

  // Free the settings structure if it was successfully created
  if (settings != nullptr) {
    settings_free(settings);
  }

  return 0;
}