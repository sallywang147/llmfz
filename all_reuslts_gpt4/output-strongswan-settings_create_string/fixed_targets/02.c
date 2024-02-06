#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::string settings_string = stream.ConsumeRandomLengthString();
  char *settings_c_string = const_cast<char*>(settings_string.c_str());

  struct settings_t *settings = settings_create_string(settings_c_string);

  if (settings != nullptr) {
    settings_destroy(settings);
  }

  return 0;
}