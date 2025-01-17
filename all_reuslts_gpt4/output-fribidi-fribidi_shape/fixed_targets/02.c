#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int flags = stream.ConsumeIntegral<int>();
  int len = stream.ConsumeIntegral<int>();
  std::vector<char> embedding_levels = stream.ConsumeBytes<char>(len);
  std::vector<char> ar_props = stream.ConsumeBytes<char>(len);
  std::vector<int> str = stream.ConsumeBytes<int>(len);

  if (len != embedding_levels.size() || len != ar_props.size() || len != str.size()) {
    return 0;
  }

  fribidi_shape(flags, embedding_levels.data(), len, ar_props.data(), str.data());

  return 0;
}