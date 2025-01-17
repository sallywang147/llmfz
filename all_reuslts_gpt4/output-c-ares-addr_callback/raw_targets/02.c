#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>

extern void addr_callback(char * , int , int , char * , int );

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int int_arg1 = stream.ConsumeIntegral<int>();
  int int_arg2 = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str1 = stream.ConsumeRandomLengthString();
  char *ptr1 = const_cast<char*>(str1.c_str());

  std::string str2 = stream.ConsumeRandomLengthString();
  char *ptr2 = const_cast<char*>(str2.c_str());

  // Call the function to fuzz
  addr_callback(ptr1, int_arg1, int_arg2, ptr2, size);

  return 0;
}