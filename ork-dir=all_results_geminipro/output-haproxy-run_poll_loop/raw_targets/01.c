#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the fuzzer.
  FuzzedDataProvider provider(data, size);

  // Read the input data.
  std::vector<uint8_t> input_data = provider.ConsumeRemainingBytes<uint8_t>();

  // Call the function under test.
  run_poll_loop();

  // Return 0 to indicate success.
  return 0;
}