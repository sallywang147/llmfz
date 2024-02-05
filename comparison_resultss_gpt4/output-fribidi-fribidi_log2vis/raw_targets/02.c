#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int len = stream.remaining_bytes() / sizeof(int);
  if (len == 0) {
    return 0;
  }

  std::vector<int> str = stream.ConsumeBytes<int>(len * sizeof(int));
  int pbase_dir = stream.ConsumeIntegral<int>();
  std::vector<int> visual_str(len);
  std::vector<int> positions_L_to_V(len);
  std::vector<int> positions_V_to_L(len);
  std::vector<char> embedding_levels(len);

  fribidi_log2vis(str.data(), len, &pbase_dir, visual_str.data(), positions_L_to_V.data(), positions_V_to_L.data(), embedding_levels.data());

  return 0;
}