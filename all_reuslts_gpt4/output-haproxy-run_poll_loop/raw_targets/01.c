#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Since the function run_poll_loop() does not have any parameters, we don't need to generate any inputs.
  // However, we can use the fuzzing data to control the number of times we call the function.
  int num_iterations = stream.ConsumeIntegralInRange<int>(1, 100);
  for (int i = 0; i < num_iterations; ++i) {
    run_poll_loop();
  }

  return 0;
}