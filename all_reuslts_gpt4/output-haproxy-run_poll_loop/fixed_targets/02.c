#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Since run_poll_loop() function does not take any parameters, we don't need to generate any input data.
  run_poll_loop();

  return 0;
}