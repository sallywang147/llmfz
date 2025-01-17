#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "speex/speex.h"
#include "speex/speex_bits.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 20) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  const int array_size = 20;
  float target[array_size] = {};
  float sw[array_size] = {};
  float ak[array_size] = {};
  float awk1[array_size] = {};
  float awk2[array_size] = {};
  float exc[array_size] = {};
  char par[array_size] = {};
  float exc2[array_size] = {};
  float r[array_size] = {};
  float cumul_gain[array_size] = {};

  int start = stream.ConsumeIntegral<int>();
  int end = stream.ConsumeIntegral<int>();
  float pitch_coef = stream.ConsumeFloatingPoint<float>();
  int p = stream.ConsumeIntegral<int>();
  int nsf = stream.ConsumeIntegral<int>();
  SpeexBits bits;
  speex_bits_init(&bits);
  char stack[array_size] = {};
  int complexity = stream.ConsumeIntegral<int>();
  int cdbk_offset = stream.ConsumeIntegral<int>();
  int plc_tuning = stream.ConsumeIntegral<int>();

  pitch_search_3tap(target, sw, ak, awk1, awk2, exc, par, start, end, pitch_coef, p, nsf, &bits, stack, exc2, r, complexity, cdbk_offset, plc_tuning, cumul_gain);

  speex_bits_destroy(&bits);

  return 0;
}