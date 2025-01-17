#include <fuzzer/FuzzedDataProvider.h>
#include <highwayhash/highwayhash_cat.h>
#include <highwayhash/highwayhash_target.h>
#include <highwayhash/string_view.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract key and hash
  bool key = stream.ConsumeBool();
  bool hash = stream.ConsumeBool();

  // Extract num_fragments
  size_t num_fragments = stream.ConsumeIntegral<size_t>();

  // Extract fragments
  std::vector<highwayhash::StringView> fragments;
  for (size_t i = 0; i < num_fragments; ++i) {
    std::string fragment = stream.ConsumeRandomLengthString();
    fragments.push_back(highwayhash::StringView(fragment));
  }

  // Execute the function
  highwayhash::HighwayHashCat<2u> hasher;
  hasher.operator()(std::integral_constant<size_t, 2>(), key, fragments.data(), num_fragments, hash);

  return 0;
}