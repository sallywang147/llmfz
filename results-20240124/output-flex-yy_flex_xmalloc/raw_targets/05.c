 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int size_arg = stream.ConsumeIntegral<int>();
  char *res = yy_flex_xmalloc(size_arg);
  free(res);
  return 0;
}