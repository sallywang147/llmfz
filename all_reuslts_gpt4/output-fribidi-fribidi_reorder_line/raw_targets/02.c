#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int flags = stream.ConsumeIntegral<int>();
  int len = stream.ConsumeIntegral<int>();
  int False = stream.ConsumeIntegral<int>();
  int base_dir = stream.ConsumeIntegral<int>();

  std::vector<int> bidi_types = stream.ConsumeBytes<int>(len);
  std::vector<char> embedding_levels = stream.ConsumeBytes<char>(len);
  std::vector<int> visual_str = stream.ConsumeBytes<int>(len);
  std::vector<int> map = stream.ConsumeBytes<int>(len);

  if (bidi_types.size() < len || embedding_levels.size() < len || visual_str.size() < len || map.size() < len) {
    return 0;
  }

  fribidi_reorder_line(flags, bidi_types.data(), len, False, base_dir, embedding_levels.data(), visual_str.data(), map.data());

  return 0;
}