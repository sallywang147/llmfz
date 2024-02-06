#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

struct param {
  int a;
  int b;
  int c;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct param p;
  p.a = stream.ConsumeIntegral<int>();
  p.b = stream.ConsumeIntegral<int>();
  p.c = stream.ConsumeIntegral<int>();
  const int seed = stream.ConsumeIntegral<int>();
  const int flags = stream.ConsumeIntegral<int>();
  mutate(&p, seed, flags);
  return 0;
}