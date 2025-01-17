#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Assume the struct param is defined as:
struct param {
  int a;
  float b;
  char c;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract values for struct param
  param p;
  p.a = stream.ConsumeIntegral<int>();
  p.b = stream.ConsumeFloatingPoint<float>();
  p.c = stream.ConsumeIntegral<char>();

  // Extract seed and flags
  int seed = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();

  mutate(&p, seed, flags);

  return 0;
}