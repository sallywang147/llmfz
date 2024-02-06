#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "M3MemoryHeader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int int_arg = stream.ConsumeIntegral<int>();
  size_t size_arg = stream.ConsumeIntegral<size_t>();

  // Extract floating point values
  double double_arg = stream.ConsumeFloatingPoint<double>();

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<char*> char_ptr_vec = stream.ConsumeBytes<char*>(stream.ConsumeIntegralInRange(0, size_arg));
  char** char_ptr_arr = char_ptr_vec.data();

  // Extract to user defined object
  struct M3MemoryHeader obj;
  size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  // Call the function to fuzz
  op_Compile(char_ptr_arr, &int_arg, &obj, size_arg, double_arg);

  return 0;
}