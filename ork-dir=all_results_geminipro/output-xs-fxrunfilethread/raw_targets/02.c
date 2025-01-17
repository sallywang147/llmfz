#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const std::string input = provider.ConsumeRemainingBytesAsString();
  char * input_c_str = strdup(input.c_str());
  char * output = fxRunFileThread(input_c_str);
  free(input_c_str);
  free(output);
  return 0;
}