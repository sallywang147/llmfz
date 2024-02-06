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
  // Initialize the settings struct to zero
  memset(&settings, 0, sizeof(settings));

  std::string pattern = stream.ConsumeRandomLengthString();
  bool merge = stream.ConsumeBool();
  std::string key = stream.ConsumeRandomLengthString();

  load_files_section(&settings, const_cast<char *>(pattern.c_str()), merge, const_cast<char *>(key.c_str()));

  return 0;
}