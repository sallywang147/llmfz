#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dnserv.h"

// Dummy function to pass as parameter.
void dummy_func() {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  short short_arg = stream.ConsumeIntegral<short>();

  // Extract to user defined object
  struct ip4_addr ip4;
  size_t consumed = stream.ConsumeData(&ip4, sizeof(ip4));

  // Call the function under test.
  dnserv_init(&ip4, short_arg, &dummy_func);

  return 0;
}