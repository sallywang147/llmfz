#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  size_t size_arg = stream.ConsumeIntegral<size_t>();
  size_t max_size_arg = stream.ConsumeIntegral<size_t>();
  int int_arg = stream.ConsumeIntegral<int>();

  // Extract a string
  std::string str = stream.ConsumeRandomLengthString();
  char *data_ptr = const_cast<char*>(str.c_str());

  // Call the function to fuzz
  LLVMFuzzerCustomMutator(data_ptr, size_arg, max_size_arg, int_arg);

  return 0;
}