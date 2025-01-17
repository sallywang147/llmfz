#include <stdint.h>
#include <stdlib.h>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int vkEnumerateInstanceVersion(int *);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int version = stream.ConsumeIntegral<int>();

  vkEnumerateInstanceVersion(&version);

  return 0;
}