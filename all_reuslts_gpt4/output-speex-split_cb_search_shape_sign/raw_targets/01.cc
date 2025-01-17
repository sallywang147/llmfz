#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "speex/speex_bits.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int p = stream.ConsumeIntegral<int>();
  const int nsf = stream.ConsumeIntegral<int>();
  const int complexity = stream.ConsumeIntegral<int>();
  const int update_target = stream.ConsumeIntegral<int>();

  // Consume data for float pointers
  std::vector<float> target_data = stream.ConsumeBytes<float>(p);
  std::vector<float> ak_data = stream.ConsumeBytes<float>(p);
  std::vector<float> awk1_data = stream.ConsumeBytes<float>(p);
  std::vector<float> awk2_data = stream.ConsumeBytes<float>(p);
  std::vector<float> exc_data = stream.ConsumeBytes<float>(nsf);
  std::vector<float> r_data = stream.ConsumeBytes<float>(nsf);

  // Consume data for char pointers
  std::string par_data = stream.ConsumeBytesAsString(p);
  std::string stack_data = stream.ConsumeRemainingBytesAsString();

  // Initialize SpeexBits
  SpeexBits bits;
  speex_bits_init(&bits);

  // Call the target function
  split_cb_search_shape_sign(target_data.data(), ak_data.data(), awk1_data.data(), awk2_data.data(), 
                             par_data.data(), p, nsf, exc_data.data(), r_data.data(), &bits, 
                             stack_data.data(), complexity, update_target);

  // Destroy SpeexBits
  speex_bits_destroy(&bits);

  return 0;
}