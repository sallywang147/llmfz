#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wtf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  
  // Consume a string from the data provider.
  std::string str = provider.ConsumeRemainingBytesAsString();
  char* s = const_cast<char*>(str.c_str());

  // Consume an integer in the range of valid CES values.
  int ces = provider.ConsumeIntegralInRange<int>(0, 255);

  // Call the function under test.
  char* result = wtf_conv_fit(s, ces);

  // Free the result string.
  free(result);

  return 0;
}