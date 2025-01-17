#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "M3MemoryHeader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int int_arg = stream.ConsumeIntegral<int>();
  size_t size_arg = stream.ConsumeIntegral<size_t>();
  double double_arg = stream.ConsumeFloatingPoint<double>();

  // Extract an array of bytes as a vector.
  size_t array_size = stream.ConsumeIntegralInRange<size_t>(0, 10);
  std::vector<char*> char_array = stream.ConsumeBytes<char*>(array_size);

  // Extract to user defined object
  struct M3MemoryHeader obj;
  size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  // Call the function with the fuzzed inputs
  char* result = op_CallIndirect(char_array.data(), &int_arg, &obj, size_arg, double_arg);

  return 0;
}