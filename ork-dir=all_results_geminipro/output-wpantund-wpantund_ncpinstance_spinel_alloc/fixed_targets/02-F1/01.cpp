#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <string>

#include "wpantund.h"

extern "C" {
#include "spinel-lowpan.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::map<std::string, std::string> settings;
  size_t num_settings = stream.ConsumeIntegral<size_t>();
  for (size_t i = 0; i < num_settings; i++) {
    const std::string key = stream.ConsumeRemainingBytesAsString();
    const std::string value = stream.ConsumeRemainingBytesAsString();
    settings.insert(std::make_pair(key, value));
  }
  nl::wpantund::NCPInstance* ncp_instance =
      nl::wpantund::wpantund_ncpinstance_spinel_alloc(&settings);
  delete ncp_instance;
  return 0;
}