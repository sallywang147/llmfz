#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t num_elements = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<int> str(num_elements);
  std::vector<int> pbase_dir(num_elements);
  std::vector<int> visual_str(num_elements);
  std::vector<int> positions_L_to_V(num_elements);
  std::vector<int> positions_V_to_L(num_elements);
  std::vector<char> embedding_levels(num_elements);

  for (size_t i = 0; i < num_elements; i++) {
    str[i] = stream.ConsumeIntegral<int>();
    pbase_dir[i] = stream.ConsumeIntegral<int>();
    visual_str[i] = stream.ConsumeIntegral<int>();
    positions_L_to_V[i] = stream.ConsumeIntegral<int>();
    positions_V_to_L[i] = stream.ConsumeIntegral<int>();
    embedding_levels[i] = stream.ConsumeIntegral<char>();
  }

  char result = fribidi_log2vis(str.data(), num_elements, pbase_dir.data(),
                                visual_str.data(), positions_L_to_V.data(),
                                positions_V_to_L.data(), embedding_levels.data());
  if (result != 0) {
    abort();
  }

  return 0;
}