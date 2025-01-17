#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>

#include "NCPInstance.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::map<std::string, std::string> settings;

  while (stream.remaining_bytes() > 0) {
    std::string key = stream.ConsumeRandomLengthString();
    std::string value = stream.ConsumeRandomLengthString();
    settings[key] = value;
  }

  nl::wpantund::NCPInstance* instance = wpantund_ncpinstance_spinel_alloc(&settings);

  // The instance is not used in this test, but in a real fuzzing scenario
  // you would want to do something with it here.

  // If the function dynamically allocates memory for the instance, you would
  // also want to free it here to prevent a memory leak. Since this is a mock
  // function, we don't know whether it does that, so we'll leave this
  // commented out for now.
  // delete instance;

  return 0;
}