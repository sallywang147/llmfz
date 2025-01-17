#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int processor = stream.ConsumeIntegral<int>();

  cpuinfo_linux_get_processor_min_frequency(processor);

  return 0;
}