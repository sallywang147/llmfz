#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

#include "lib/b2nd/b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int dim = stream.ConsumeIntegral<int>() % 4;
  int x = stream.ConsumeIntegral<int>();
  int y = stream.ConsumeIntegral<int>();
  int z = stream.ConsumeIntegral<int>();
  int t = stream.ConsumeIntegral<int>();
  int n = stream.ConsumeIntegral<int>();
  int m = stream.ConsumeIntegral<int>();
  int p = stream.ConsumeIntegral<int>();
  int q = stream.ConsumeIntegral<int>();
  int r = stream.ConsumeIntegral<int>();
  int s = stream.ConsumeIntegral<int>();
  int u = stream.ConsumeIntegral<int>();
  int v = stream.ConsumeIntegral<int>();
  int w = stream.ConsumeIntegral<int>();

  b2nd_array_t* array = b2nd_array_new(dim, x, y, z, t, n, m, p, q, r, s, u, v, w);
  if (array == nullptr) {
    return 0;
  }

  const std::string filename = stream.ConsumeRemainingBytesAsString();

  b2nd_save(array, filename.c_str());

  b2nd_array_free(array);
  return 0;
}