#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "highwayhash/highwayhash_cat.h"
#include "highwayhash/string_view.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::integral_constant<uint64_t, 4u> integral_constant;
  bool key = stream.ConsumeBool();
  size_t num_fragments = stream.ConsumeIntegral<size_t>();
  size_t hash;

  std::vector<highwayhash::StringView> fragments;
  for (size_t i = 0; i < num_fragments; i++) {
    std::string str = stream.ConsumeRandomLengthString();
    fragments.push_back(highwayhash::StringView(str));
  }

  highwayhash::HighwayHashCat<integral_constant> hashcat;
  hashcat(&integral_constant, key, fragments.data(), num_fragments, &hash);

  return 0;
}