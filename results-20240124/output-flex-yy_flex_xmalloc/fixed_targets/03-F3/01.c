#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include <FlexLexer.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int size_to_allocate = stream.ConsumeIntegral<int>();
  char *ptr = yy_flex_xmalloc(size_to_allocate);
  free(ptr);
  return 0;
}