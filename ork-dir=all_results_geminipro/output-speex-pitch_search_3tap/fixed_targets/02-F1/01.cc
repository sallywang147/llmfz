#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "speex/speex_bits.h"
#include "speex/speex_header.h"
#include "speex/speex_preprocess.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<float> target(stream.ConsumeIntegralInRange<size_t>(0, 100));
  stream.ConsumeFloatArray(&target[0], target.size());
  std::vector<float> sw(stream.ConsumeIntegralInRange<size_t>(0, 100));
  stream.ConsumeFloatArray(&sw[0], sw.size());
  std::vector<float> ak(stream.ConsumeIntegralInRange<size_t>(0, 100));
  stream.ConsumeFloatArray(&ak[0], ak.size());
  std::vector<float> awk1(stream.ConsumeIntegralInRange<size_t>(0, 100));
  stream.ConsumeFloatArray(&awk1[0], awk1.size());
  std::vector<float> awk2(stream.ConsumeIntegralInRange<size_t>(0, 100));
  stream.ConsumeFloatArray(&awk2[0], awk2.size());
  std::vector<float> exc(stream.ConsumeIntegralInRange<size_t>(0, 100));
  stream.ConsumeFloatArray(&exc[0], exc.size());
  std::vector<char> par(stream.ConsumeIntegralInRange<size_t>(0, 100));
  stream.ConsumeBytes(&par[0], par.size());
  const int start = stream.ConsumeIntegral<int>();
  const int end = stream.ConsumeIntegral<int>();
  const float pitch_coef = stream.ConsumeFloatingPoint<float>();
  const int p = stream.ConsumeIntegral<int>();
  const int nsf = stream.ConsumeIntegral<int>();
  struct SpeexBits bits;
  const int complexity = stream.ConsumeIntegral<int>();
  const int cdbk_offset = stream.ConsumeIntegral<int>();
  const int plc_tuning = stream.ConsumeIntegral<int>();
  std::vector<float> cumul_gain(stream.ConsumeIntegralInRange<size_t>(0, 100));
  stream.ConsumeFloatArray(&cumul_gain[0], cumul_gain.size());

  pitch_search_3tap(&target[0], &sw[0], &ak[0], &awk1[0], &awk2[0], &exc[0],
                    &par[0], start, end, pitch_coef, p, nsf, &bits, nullptr,
                    nullptr, nullptr, complexity, cdbk_offset, plc_tuning,
                    &cumul_gain[0]);
  return 0;
}