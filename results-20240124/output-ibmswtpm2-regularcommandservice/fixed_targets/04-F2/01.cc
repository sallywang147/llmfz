#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "RegularCommandService.h"

extern "C" {
#include "RegularCommandService.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int port_number = stream.ConsumeIntegral<int>();
  RegularCommandService(port_number);
  return 0;
}