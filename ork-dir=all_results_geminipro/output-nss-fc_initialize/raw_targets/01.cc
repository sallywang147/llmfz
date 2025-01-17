#include <fuzzer/FuzzedDataProvider.h>

extern "C" size_t FC_Initialize(char *);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRandomLengthString(size);
  char *ptr = str.c_str();
  FC_Initialize(ptr);
  return 0;
}