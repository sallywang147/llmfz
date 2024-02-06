#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "private_settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  private_settings_t settings;
  std::string str = stream.ConsumeRandomLengthString();
  char *settings_str = const_cast<char*>(str.c_str());
  bool merge = stream.ConsumeBool();

  load_string(&settings, settings_str, merge);

  return 0;
}