#include <cstdint>
#include <cstdlib>
#include <fuzzer/FuzzedDataProvider.h>

#include "jbig2.h"

extern "C" {
#include "jbig2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t alloc_size = stream.ConsumeIntegral<size_t>();
  jbig2_default_alloc(NULL, alloc_size);
  return 0;
}