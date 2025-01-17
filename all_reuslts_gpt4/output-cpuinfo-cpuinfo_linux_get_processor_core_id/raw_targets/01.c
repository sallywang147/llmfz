#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int processor = stream.ConsumeIntegral<int>();
  int core_id;

  cpuinfo_linux_get_processor_core_id(processor, &core_id);

  return 0;
}