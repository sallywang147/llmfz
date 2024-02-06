#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>

#include "wpantund/NCPInstance.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::map<std::string, std::string> settings;
  while (stream.remaining_bytes() > 0) {
    std::string key = stream.ConsumeRandomLengthString();
    std::string value = stream.ConsumeRandomLengthString();
    settings[key] = value;
  }
  
  nl::wpantund::NCPInstance *instance = wpantund_ncpinstance_spinel_alloc(&settings);
  if (instance != nullptr) {
    // Do something with instance
    // ...
    delete instance;
  }
  
  return 0;
}