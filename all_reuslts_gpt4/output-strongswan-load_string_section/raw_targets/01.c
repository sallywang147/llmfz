#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

#include "private_settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the private_settings_t struct
  struct private_settings_t private_settings;

  // Consume data for the settings string
  std::string settings = stream.ConsumeRandomLengthString();
  char* settings_ptr = const_cast<char*>(settings.c_str());

  // Consume data for the merge boolean
  bool merge = stream.ConsumeBool();

  // Consume data for the key string
  std::string key = stream.ConsumeRandomLengthString();
  char* key_ptr = const_cast<char*>(key.c_str());

  // Call the function under test
  load_string_section(&private_settings, settings_ptr, merge, key_ptr);

  return 0;
}