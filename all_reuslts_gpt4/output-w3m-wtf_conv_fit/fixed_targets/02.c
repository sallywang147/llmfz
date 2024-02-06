#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" char * wtf_conv_fit(char * s, int ces);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  std::string str = provider.ConsumeRemainingBytesAsString();
  char* s = const_cast<char*>(str.c_str());

  int ces = provider.ConsumeIntegral<int>();

  char* result = wtf_conv_fit(s, ces);

  return 0;
}