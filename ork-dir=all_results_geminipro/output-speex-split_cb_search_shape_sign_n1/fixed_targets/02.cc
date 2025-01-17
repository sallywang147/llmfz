#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "speex/speex.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<float> target(stream.ConsumeIntegralInRange<size_t>(0, 100), 0.0);
  std::vector<float> ak(stream.ConsumeIntegralInRange<size_t>(0, 100), 0.0);
  std::vector<float> awk1(stream.ConsumeIntegralInRange<size_t>(0, 100), 0.0);
  std::vector<float> awk2(stream.ConsumeIntegralInRange<size_t>(0, 100), 0.0);
  std::vector<char> par(stream.ConsumeIntegralInRange<size_t>(0, 100), 0);
  int p = stream.ConsumeIntegral<int>();
  int nsf = stream.ConsumeIntegral<int>();
  std::vector<float> exc(stream.ConsumeIntegralInRange<size_t>(0, 100), 0.0);
  std::vector<float> r(stream.ConsumeIntegralInRange<size_t>(0, 100), 0.0);
  struct SpeexBits bits;
  std::memset(&bits, 0, sizeof(bits));
  std::vector<char> stack(stream.ConsumeIntegralInRange<size_t>(0, 100), 0);
  int update_target = stream.ConsumeIntegral<int>();

  // Fix the function call to use the correct function name.
  speex_preprocess_state_split_cb_search_shape_sign_N1(target.data(), ak.data(), awk1.data(), awk2.data(),
                                par.data(), p, nsf, exc.data(), r.data(), &bits,
                                stack.data(), update_target);
  return 0;
}