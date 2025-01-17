#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "speex/speex_bits.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int p = stream.ConsumeIntegral<int>();
  const int nsf = stream.ConsumeIntegral<int>();
  const int update_target = stream.ConsumeIntegral<int>();
  
  std::vector<float> target_vec = stream.ConsumeBytes<float>(p);
  std::vector<float> ak_vec = stream.ConsumeBytes<float>(p);
  std::vector<float> awk1_vec = stream.ConsumeBytes<float>(p);
  std::vector<float> awk2_vec = stream.ConsumeBytes<float>(p);
  std::vector<float> exc_vec = stream.ConsumeBytes<float>(nsf);
  std::vector<float> r_vec = stream.ConsumeBytes<float>(nsf);
  
  std::string par_str = stream.ConsumeBytesAsString(p);
  std::string stack_str = stream.ConsumeBytesAsString(nsf);

  SpeexBits bits;
  speex_bits_init(&bits);

  if(target_vec.size() < p || ak_vec.size() < p || awk1_vec.size() < p || awk2_vec.size() < p || exc_vec.size() < nsf || r_vec.size() < nsf || par_str.size() < p || stack_str.size() < nsf) {
    return 0;
  }

  split_cb_search_shape_sign_N1(target_vec.data(), ak_vec.data(), awk1_vec.data(), awk2_vec.data(), const_cast<char*>(par_str.c_str()), p, nsf, exc_vec.data(), r_vec.data(), &bits, const_cast<char*>(stack_str.c_str()), update_target);

  speex_bits_destroy(&bits);

  return 0;
}