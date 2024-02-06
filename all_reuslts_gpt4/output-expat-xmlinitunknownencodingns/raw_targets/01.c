#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "expat.h"

// Define a dummy function for the `convert` parameter.
static int dummy_convert(void* /*unused*/, const char* /*unused*/) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Consume some data for `mem` and `userData` parameters.
  std::string mem = provider.ConsumeBytesAsString(provider.remaining_bytes() / 2);
  std::string userData = provider.ConsumeRemainingBytesAsString();

  // Initialize `table` parameter.
  int table[256];
  for (int& i : table) {
    i = provider.ConsumeIntegral<int>();
  }

  // Call the target function.
  struct encoding* result = XmlInitUnknownEncodingNS(
      const_cast<char*>(mem.c_str()), table, dummy_convert, const_cast<char*>(userData.c_str()));

  // We don't use the result, because this is a fuzzing harness.
  // In a real application, you would want to use the result somehow.

  return 0;
}