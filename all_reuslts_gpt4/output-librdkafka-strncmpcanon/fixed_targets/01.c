#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int strncmpcanon(char * a, char * b, int n);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Split the input data into two strings.
  const size_t a_size = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  std::string a = stream.ConsumeBytesAsString(a_size);
  std::string b = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz.
  strncmpcanon(const_cast<char*>(a.c_str()), const_cast<char*>(b.c_str()), a.size());

  return 0;
}