#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "regex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Initialize the parse structure
  struct parse p;
  p.next = provider.data();
  p.end = p.next + provider.size();
  p.error = 0;
  p.ncsalloc = 0;

  // Consume an int from the data
  int flag = provider.ConsumeIntegral<int>();

  // Call the function to fuzz
  p_simp_re(&p, flag);

  return 0;
}