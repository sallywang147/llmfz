#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "speex/speex_bits.h"
#include "speex/speex_preprocess.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<float> target(stream.ConsumeIntegralInRange<int>(1, 1000));
  stream.ConsumeFloatArray(target.data(), target.size());
  std::vector<float> ak(stream.ConsumeIntegralInRange<int>(1, 1000));
  stream.ConsumeFloatArray(ak.data(), ak.size());
  std::vector<float> awk1(stream.ConsumeIntegralInRange<int>(1, 1000));
  stream.ConsumeFloatArray(awk1.data(), awk1.size());
  std::vector<float> awk2(stream.ConsumeIntegralInRange<int>(1, 1000));
  stream.ConsumeFloatArray(awk2.data(), awk2.size());
  std::vector<char> par(stream.ConsumeIntegralInRange<int>(1, 1000));
  stream.ConsumeBytes(par.data(), par.size());
  const int p = stream.ConsumeIntegralInRange<int>(1, 1000);
  const int nsf = stream.ConsumeIntegralInRange<int>(1, 1000);
  std::vector<float> exc(stream.ConsumeIntegralInRange<int>(1, 1000));
  stream.ConsumeFloatArray(exc.data(), exc.size());
  std::vector<float> r(stream.ConsumeIntegralInRange<int>(1, 1000));
  stream.ConsumeFloatArray(r.data(), r.size());
  struct SpeexBits bits;
  std::vector<char> stack(stream.ConsumeIntegralInRange<int>(1, 1000));
  stream.ConsumeBytes(stack.data(), stack.size());
  const int update_target = stream.ConsumeIntegralInRange<int>(0, 1);

  split_cb_search_shape_sign_N1(target.data(), ak.data(), awk1.data(), awk2.data(),
                              par.data(), p, nsf, exc.data(), r.data(), &bits,
                              stack.data(), update_target);
  return 0;
}