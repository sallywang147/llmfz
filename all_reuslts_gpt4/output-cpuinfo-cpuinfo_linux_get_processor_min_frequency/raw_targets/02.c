#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract integer for processor id
  int processor = stream.ConsumeIntegral<int>();

  // Call the function with the fuzzed input
  cpuinfo_linux_get_processor_min_frequency(processor);

  return 0;
}