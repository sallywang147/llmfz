#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "cpuinfo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int processor = stream.ConsumeIntegral<int>();
  int package_id = 0;
  cpuinfo_linux_get_processor_package_id(processor, &package_id);

  return 0;
}