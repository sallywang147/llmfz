#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wx/mem.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t free_memory = wxGetFreeMemory();
  if (free_memory == 0) {
    return 0;
  }
  const size_t bytes_to_allocate =
      stream.ConsumeIntegralInRange<size_t>(1, free_memory);
  void* ptr = malloc(bytes_to_allocate);
  if (ptr == nullptr) {
    return 0;
  }
  free(ptr);
  return 0;
}