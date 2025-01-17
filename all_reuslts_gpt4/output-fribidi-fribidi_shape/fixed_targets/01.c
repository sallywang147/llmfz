#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int flags = provider.ConsumeIntegral<int>();
  int len = provider.ConsumeIntegralInRange<int>(0, size);
  
  std::vector<char> embedding_levels = provider.ConsumeBytes<char>(len);
  std::vector<char> ar_props = provider.ConsumeBytes<char>(len);
  std::vector<int> str = provider.ConsumeBytes<int>(len);

  fribidi_shape(flags, embedding_levels.data(), len, ar_props.data(), str.data());

  return 0;
}