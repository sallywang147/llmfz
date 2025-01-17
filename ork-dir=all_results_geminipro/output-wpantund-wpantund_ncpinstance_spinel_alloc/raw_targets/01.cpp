#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <string>

#include "wpantund.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::map<std::string, std::string> settings;
  while (stream.remaining_bytes() > 0) {
    const std::string key = stream.ConsumeRandomLengthString();
    const std::string value = stream.ConsumeRandomLengthString();
    settings[key] = value;
  }

  nl::wpantund::NCPInstance* instance =
      wpantund_ncpinstance_spinel_alloc(&settings);
  if (instance != nullptr) {
    wpantund_ncpinstance_spinel_free(instance);
  }
  return 0;
}