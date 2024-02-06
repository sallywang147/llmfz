#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "private_settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct private_settings_t settings;

  // Extract a string for the settings parameter
  std::string settings_str = stream.ConsumeRandomLengthString();
  char *settings_ptr = const_cast<char *>(settings_str.c_str());

  // Extract a boolean for the merge parameter
  bool merge = stream.ConsumeBool();

  // Extract a string for the key parameter
  std::string key_str = stream.ConsumeRandomLengthString();
  char *key_ptr = const_cast<char *>(key_str.c_str());

  load_string_section(&settings, settings_ptr, merge, key_ptr);

  return 0;
}