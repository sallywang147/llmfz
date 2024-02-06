#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int flags = stream.ConsumeIntegral<int>();
  int len = stream.remaining_bytes() / 2; // We need to reserve space for both embedding_levels and ar_props
  if (len == 0) {
    return 0;
  }

  std::vector<char> embedding_levels = stream.ConsumeBytes<char>(len);
  std::vector<char> ar_props = stream.ConsumeBytes<char>(len);
  std::vector<int> str(len);

  fribidi_shape_arabic(flags, embedding_levels.data(), len, ar_props.data(), str.data());

  return 0;
}