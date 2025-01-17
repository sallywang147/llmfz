#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "speex/speex.h"
#include "speex/speex_bits.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int p = stream.ConsumeIntegralInRange<int>(1, 10);
  const int nsf = stream.ConsumeIntegralInRange<int>(1, 10);
  const int update_target = stream.ConsumeIntegral<int>();
  std::vector<float> target(p, 0.0);
  std::vector<float> ak(p, 0.0);
  std::vector<float> awk1(p, 0.0);
  std::vector<float> awk2(p, 0.0);
  std::vector<float> exc(nsf, 0.0);
  std::vector<float> r(nsf, 0.0);
  std::vector<char> par(p, 0);
  std::vector<char> stack(1024, 0);
  SpeexBits bits;
  speex_bits_init(&bits);

  split_cb_search_shape_sign_N1(target.data(), ak.data(), awk1.data(), awk2.data(), par.data(), p, nsf, exc.data(), r.data(), &bits, stack.data(), update_target);

  speex_bits_destroy(&bits);
  return 0;
}