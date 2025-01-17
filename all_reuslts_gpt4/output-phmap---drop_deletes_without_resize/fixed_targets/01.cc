#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <parallel_hashmap/phmap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the map object
  phmap::flat_hash_map<unsigned int, int> map;

  // Consume data to populate the map
  while (stream.remaining_bytes() > 0) {
    unsigned int key = stream.ConsumeIntegral<unsigned int>();
    int value = stream.ConsumeIntegral<int>();
    map[key] = value;
  }

  // Use the map size as a valid position
  size_t pos = map.size();

  // Call the target function
  map.drop_deletes_without_resize(pos);

  return 0;
}