#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fuzzer/FuzzedDataProvider.h>
#include <cwchar>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int c = stream.ConsumeIntegral<int>();
  iswdigit(c);
  return 0;
}

extern "C" int iswdigit(int c) {
  return std::iswdigit(c);
}

extern "C" int iswordchar(int c) {
  return iswdigit(c) || iswalpha(c) || c == '_';
}