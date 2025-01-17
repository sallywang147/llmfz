#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "pitch_search_3tap.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<float> target(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeFloatArray(target.data(), target.size());

  std::vector<float> sw(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeFloatArray(sw.data(), sw.size());

  std::vector<float> ak(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeFloatArray(ak.data(), ak.size());

  std::vector<float> awk1(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeFloatArray(awk1.data(), awk1.size());

  std::vector<float> awk2(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeFloatArray(awk2.data(), awk2.size());

  std::vector<float> exc(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeFloatArray(exc.data(), exc.size());

  std::vector<char> par(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeBytes(par.data(), par.size());

  const int start = stream.ConsumeIntegral<int>();
  const int end = stream.ConsumeIntegral<int>();
  const float pitch_coef = stream.ConsumeFloatingPoint<float>();
  const int p = stream.ConsumeIntegral<int>();
  const int nsf = stream.ConsumeIntegral<int>();
  const int complexity = stream.ConsumeIntegral<int>();
  const int cdbk_offset = stream.ConsumeIntegral<int>();
  const int plc_tuning = stream.ConsumeIntegral<int>();

  std::vector<float> cumul_gain(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeFloatArray(cumul_gain.data(), cumul_gain.size());

  struct SpeexBits bits;
  memset(&bits, 0, sizeof(bits));

  std::vector<char> stack(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeBytes(stack.data(), stack.size());

  std::vector<float> exc2(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeFloatArray(exc2.data(), exc2.size());

  std::vector<float> r(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  stream.ConsumeFloatArray(r.data(), r.size());

  pitch_search_3tap(target.data(), sw.data(), ak.data(), awk1.data(), awk2.data(),
                    exc.data(), par.data(), start, end, pitch_coef, p, nsf, &bits,
                    stack.data(), exc2.data(), r.data(), complexity, cdbk_offset,
                    plc_tuning, cumul_gain.data());
  return 0;
}