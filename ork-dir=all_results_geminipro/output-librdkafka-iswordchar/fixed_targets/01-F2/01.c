#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cctype>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int c = stream.ConsumeIntegral<int>();
  iswctype(c, wctype("alnum"));
  return 0;
}

extern "C" int iswordchar(int c) {
  return iswctype(c, wctype("alnum"));
}