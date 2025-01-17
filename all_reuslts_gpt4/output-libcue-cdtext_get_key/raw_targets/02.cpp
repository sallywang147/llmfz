#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" char* cdtext_get_key(int, int);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int arg1 = provider.ConsumeIntegral<int>();
  int arg2 = provider.ConsumeIntegral<int>();

  char* result = cdtext_get_key(arg1, arg2);

  return 0;
}