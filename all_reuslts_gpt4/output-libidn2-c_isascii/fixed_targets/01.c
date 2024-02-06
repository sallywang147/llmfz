#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" bool c_isascii(int c);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int c = stream.ConsumeIntegral<int>();
  (void)c_isascii(c);
  return 0;
}