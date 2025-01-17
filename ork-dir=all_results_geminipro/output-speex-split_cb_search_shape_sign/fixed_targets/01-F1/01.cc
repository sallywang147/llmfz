#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "speex/speex.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  float target[200];
  float ak[200];
  float awk1[200];
  float awk2[200];
  char par[200];
  int p = stream.ConsumeIntegral<int>();
  int nsf = stream.ConsumeIntegral<int>();
  float exc[200];
  float r[200];
  struct SpeexBits bits;
  char stack[200];
  int complexity = stream.ConsumeIntegral<int>();
  int update_target = stream.ConsumeIntegral<int>();

  split_cb_search_shape_sign(target, ak, awk1, awk2, par, p, nsf, exc, r, &bits,
                             stack, complexity, update_target);
  return 0;
}