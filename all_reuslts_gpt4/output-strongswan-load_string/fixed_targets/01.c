#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "private_settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a private_settings_t object
  struct private_settings_t settings_obj;

  // Consume data for the settings string
  std::string settings_str = stream.ConsumeRandomLengthString();
  char* settings = const_cast<char*>(settings_str.c_str());

  // Consume data for the merge boolean
  bool merge = stream.ConsumeBool();

  // Call the function to fuzz
  load_string(&settings_obj, settings, merge);

  return 0;
}