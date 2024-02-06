#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include "parallel_hashmap/phmap.h"

using MapType = phmap::flat_hash_map<unsigned int, int, phmap::Hash<unsigned int>, phmap::EqualTo<unsigned int>>;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  MapType map;

  // Fill the map with random data
  while (stream.remaining_bytes() > 4) {
    unsigned int key = stream.ConsumeIntegral<unsigned int>();
    int value = stream.ConsumeIntegral<int>();
    map[key] = value;
  }

  // Call the drop_deletes_without_resize function
  if (!map.empty()) {
    size_t pos = stream.ConsumeIntegralInRange<size_t>(0, map.size() - 1);
    map.drop_deletes_without_resize(pos);
  }

  return 0;
}