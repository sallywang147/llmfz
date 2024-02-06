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