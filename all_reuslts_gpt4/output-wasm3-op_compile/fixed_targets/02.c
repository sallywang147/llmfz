#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "op.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int int_arg = stream.ConsumeIntegral<int>();
  size_t size_arg = stream.ConsumeIntegral<size_t>();

  // Extract floating point values
  double double_arg = stream.ConsumeFloatingPoint<double>();

  // Extract an array of bytes as a vector
  std::vector<char> bytes = stream.ConsumeBytes<char>(stream.remaining_bytes());
  char* char_ptr = bytes.data();

  // Extract to user defined object
  struct M3MemoryHeader obj;
  size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  // Call the function to fuzz
  char* result = op_Compile(&char_ptr, &int_arg, &obj, size_arg, double_arg);

  return 0;
}