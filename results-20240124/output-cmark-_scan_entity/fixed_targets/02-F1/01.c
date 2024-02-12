#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "scan_entity.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char* input = (char*)malloc(input_size + 1);
  provider.ConsumeBytes(input, input_size);
  input[input_size] = '\0';

  int ret = _scan_entity(input);
  free(input);
  return ret;
}