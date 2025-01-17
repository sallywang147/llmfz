#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" char * yy_flex_xmalloc(int size);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int malloc_size = stream.ConsumeIntegral<int>();
  char* memory = yy_flex_xmalloc(malloc_size);
  if(memory != nullptr) {
    free(memory);
  }
  return 0;
}