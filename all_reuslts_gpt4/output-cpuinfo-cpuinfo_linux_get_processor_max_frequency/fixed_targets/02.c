#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data to create a processor id
  int processor = stream.ConsumeIntegral<int>();

  // Call the function with the fuzzed processor id
  cpuinfo_linux_get_processor_max_frequency(processor);

  return 0;
}