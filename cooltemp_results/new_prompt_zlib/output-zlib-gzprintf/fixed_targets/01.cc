 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zlib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gzFile file = gzdopen(0, "wb");
  if (file == nullptr) {
    return 0;
  }
  // Generate a random string.
  std::string str = stream.ConsumeRemainingBytesAsString();
  // Generate a random number for the format specifier.
  int format_specifier = stream.ConsumeIntegral<int>();
  // Generate a random number for the variable argument.
  int variable_argument = stream.ConsumeIntegral<int>();
  // Call gzprintf with the generated arguments.
  gzprintf(file, str.c_str(), format_specifier, variable_argument);
  gzclose(file);
  return 0;
}