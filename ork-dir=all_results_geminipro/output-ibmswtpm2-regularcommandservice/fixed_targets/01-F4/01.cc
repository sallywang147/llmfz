#include <stdio.h>
#include <stdlib.h>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" {
#include "RegularCommandService.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int PortNumber = stream.ConsumeIntegral<int>();
  RegularCommandService(&PortNumber);
  return 0;
}