#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" int strncmpcanon(char * a, char * b, int n);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  
  std::string str_a = provider.ConsumeBytesAsString(size / 2);
  std::string str_b = provider.ConsumeRemainingBytesAsString();

  int n = str_a.size() < str_b.size() ? str_a.size() : str_b.size();

  strncmpcanon((char*)str_a.c_str(), (char*)str_b.c_str(), n);

  return 0;
}