#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "private_settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  // Initialize the private_settings_t struct
  struct private_settings_t settings;

  // Consume data for the pattern and key
  std::string pattern = fdp.ConsumeRandomLengthString();
  std::string key = fdp.ConsumeRandomLengthString();

  // Consume data for the merge bool
  bool merge = fdp.ConsumeBool();

  // Call the target function
  load_files_section(&settings, const_cast<char*>(pattern.c_str()), merge, const_cast<char*>(key.c_str()));

  return 0;
}