#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int iterations = stream.ConsumeIntegral<int>();
  for (int i = 0; i < iterations; i++) {
    // Fix: call the function with the correct name
    run_poll_loop();
  }
  return 0;
}