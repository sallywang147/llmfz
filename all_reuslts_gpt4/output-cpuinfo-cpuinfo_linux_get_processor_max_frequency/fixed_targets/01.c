#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  int processor = stream.ConsumeIntegral<int>();

  cpuinfo_linux_get_processor_max_frequency(processor);

  return 0;
}