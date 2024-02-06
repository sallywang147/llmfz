#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "private_settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t settings_size = provider.ConsumeIntegralInRange<size_t>(0, 10000);
  std::string settings = provider.ConsumeRandomLengthString(settings_size);
  bool merge = provider.ConsumeBool();
  size_t key_size = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::string key = provider.ConsumeRandomLengthString(key_size);
  struct private_settings_t this_struct;
  bool result = load_string_section(&this_struct, settings.c_str(), merge, key.c_str());
  return result;
}