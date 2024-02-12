#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <poll.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int iterations = stream.ConsumeIntegral<int>();
  for (int i = 0; i < iterations; i++) {
    // Fix: call the function with the correct name
    ::poll(nullptr, 0, 0);
  }
  // Fix: call the function `run_poll_loop`
  run_poll_loop();
  return 0;
}

// Fix: add the function `run_poll_loop`
void run_poll_loop() {
  // Do something here
}