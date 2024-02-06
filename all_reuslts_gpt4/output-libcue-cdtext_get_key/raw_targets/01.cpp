#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" char* cdtext_get_key(int, int);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int arg1 = stream.ConsumeIntegral<int>();
  int arg2 = stream.ConsumeIntegral<int>();

  cdtext_get_key(arg1, arg2);

  return 0;
}