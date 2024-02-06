#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *input_data = const_cast<char*>(str.c_str());

  char* result = listenerRun(input_data);

  // Do something with result if necessary
  // ...

  return 0;
}