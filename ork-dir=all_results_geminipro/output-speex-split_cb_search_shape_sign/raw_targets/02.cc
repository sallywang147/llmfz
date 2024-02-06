#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t target_size = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  std::vector<float> target(target_size);
  stream.ConsumeFloatingPointArray(target.data(), target_size);

  const size_t ak_size = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  std::vector<float> ak(ak_size);
  stream.ConsumeFloatingPointArray(ak.data(), ak_size);

  const size_t awk1_size = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  std::vector<float> awk1(awk1_size);
  stream.ConsumeFloatingPointArray(awk1.data(), awk1_size);

  const size_t awk2_size = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  std::vector<float> awk2(awk2_size);
  stream.ConsumeFloatingPointArray(awk2.data(), awk2_size);

  const size_t par_size = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  std::vector<char> par(par_size);
  stream.ConsumeBytes<char>(par.data(), par_size);

  const int p = stream.ConsumeIntegral<int>();
  const int nsf = stream.ConsumeIntegral<int>();

  const size_t exc_size = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  std::vector<float> exc(exc_size);
  stream.ConsumeFloatingPointArray(exc.data(), exc_size);

  const size_t r_size = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  std::vector<float> r(r_size);
  stream.ConsumeFloatingPointArray(r.data(), r_size);

  struct SpeexBits bits;
  char stack[1000];
  const int complexity = stream.ConsumeIntegral<int>();
  const int update_target = stream.ConsumeIntegral<int>();

  split_cb_search_shape_sign(target.data(), ak.data(), awk1.data(), awk2.data(),
                             par.data(), p, nsf, exc.data(), r.data(), &bits,
                             stack, complexity, update_target);
  return 0;
}