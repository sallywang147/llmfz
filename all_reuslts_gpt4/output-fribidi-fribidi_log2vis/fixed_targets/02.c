#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int len = stream.ConsumeIntegralInRange<int>(0, 100);
  std::vector<int> str = stream.ConsumeIntegralVector<int>(len);
  int pbase_dir = stream.ConsumeIntegral<int>();
  std::vector<int> visual_str(len, 0);
  std::vector<int> positions_L_to_V(len, 0);
  std::vector<int> positions_V_to_L(len, 0);
  std::vector<char> embedding_levels(len, 0);

  fribidi_log2vis(str.data(), len, &pbase_dir, visual_str.data(), positions_L_to_V.data(), positions_V_to_L.data(), embedding_levels.data());

  return 0;
}