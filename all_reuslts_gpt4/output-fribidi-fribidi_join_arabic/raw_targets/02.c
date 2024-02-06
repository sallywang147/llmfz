#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for "len" parameter
  const int len = stream.ConsumeIntegralInRange<int>(0, size);

  // Consume data for "bidi_types" parameter
  std::vector<int> bidi_types = stream.ConsumeBytes<int>(len);
  if (bidi_types.empty()) {
    return 0;
  }

  // Consume data for "embedding_levels" parameter
  std::vector<char> embedding_levels = stream.ConsumeBytes<char>(len);
  if (embedding_levels.empty()) {
    return 0;
  }

  // Consume data for "ar_props" parameter
  std::vector<char> ar_props = stream.ConsumeBytes<char>(len);
  if (ar_props.empty()) {
    return 0;
  }

  // Call the function to be fuzzed
  fribidi_join_arabic(bidi_types.data(), len, embedding_levels.data(), ar_props.data());

  return 0;
}