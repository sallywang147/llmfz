#include <fuzzer/FuzzedDataProvider.h>
#include <parallel_hashmap/phmap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the hash set
  phmap::flat_hash_map<std::string, std::string> map;

  // Consume data to populate the map
  while (stream.remaining_bytes() > 0) {
    std::string key = stream.ConsumeRandomLengthString();
    std::string value = stream.ConsumeRandomLengthString();
    map[key] = value;
  }

  // Get the iterator
  auto iter = map.begin();

  // Call the operator++ function
  if (iter != map.end()) {
    ++iter;
  }

  return 0;
}