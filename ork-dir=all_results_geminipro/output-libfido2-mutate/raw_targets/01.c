#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct param p;
  const int seed = stream.ConsumeIntegral<int>();
  const int flags = stream.ConsumeIntegral<int>();
  mutate(&p, seed, flags);
  return 0;
}