#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

struct M3MemoryHeader {};

extern "C" char * op_CallIndirect(char ** , int * , struct M3MemoryHeader * , size_t , double );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t array_size = stream.remaining_bytes() / 2;
  std::vector<char*> char_ptr_array = stream.ConsumeBytes<char*>(array_size);
  char **char_ptr = char_ptr_array.data();

  int int_arg = stream.ConsumeIntegral<int>();

  struct M3MemoryHeader mem_header;

  size_t size_arg = stream.ConsumeIntegral<size_t>();

  double double_arg = stream.ConsumeFloatingPoint<double>();

  op_CallIndirect(char_ptr, &int_arg, &mem_header, size_arg, double_arg);

  return 0;
}