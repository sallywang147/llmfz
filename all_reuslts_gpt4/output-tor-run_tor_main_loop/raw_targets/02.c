#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int run_tor_main_loop();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Since the function does not take any arguments, we don't need to generate any inputs.
  // Just call the function.
  run_tor_main_loop();

  return 0;
}