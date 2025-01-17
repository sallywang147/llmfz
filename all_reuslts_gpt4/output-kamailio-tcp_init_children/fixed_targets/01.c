#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int tcp_init_children(int * woneinit);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  int woneinit = stream.ConsumeIntegral<int>();
  tcp_init_children(&woneinit);

  return 0;
}