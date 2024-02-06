#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t len = stream.ConsumeIntegralInRange<size_t>(1, 100);
  if (stream.remaining_bytes() < len * 3) {
    return 0;
  }

  std::vector<int> bidi_types(len);
  std::vector<char> embedding_levels(len);
  std::vector<char> ar_props(len);

  for (size_t i = 0; i < len; ++i) {
    bidi_types[i] = stream.ConsumeIntegral<int>();
    embedding_levels[i] = stream.ConsumeIntegral<char>();
    ar_props[i] = stream.ConsumeIntegral<char>();
  }

  fribidi_join_arabic(bidi_types.data(), len, embedding_levels.data(), ar_props.data());

  return 0;
}