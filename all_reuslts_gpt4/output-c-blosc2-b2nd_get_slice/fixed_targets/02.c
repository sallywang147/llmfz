#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct b2nd_context_s context;
  struct b2nd_array_t.161* array1;
  struct b2nd_array_t array2;
  size_t size1 = stream.ConsumeIntegral<size_t>();
  size_t size2 = stream.ConsumeIntegral<size_t>();

  b2nd_get_slice(&context, &array1, &array2, &size1, &size2);

  return 0;
}