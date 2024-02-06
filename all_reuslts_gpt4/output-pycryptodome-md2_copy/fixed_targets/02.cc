#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct hash_state src, dst;

  // Initialize the src hash_state with random data
  size_t consumed = stream.ConsumeData(&src, sizeof(src));
  if (consumed != sizeof(src)) {
    return 0;
  }

  // Call the function under test
  md2_copy(&src, &dst);

  return 0;
}