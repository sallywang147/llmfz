#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    // Initialize global state here.
    initialized = true;
  }

  // Use the data provided by libFuzzer.
  FuzzedDataProvider provider(data, size);

  // Read some integers from the data.
  std::vector<int> integers;
  while (provider.remaining_bytes() > 0) {
    integers.push_back(provider.ConsumeIntegral<int>());
  }

  // Call the function to be fuzzed.
  mworker_loop();

  return 0;
}