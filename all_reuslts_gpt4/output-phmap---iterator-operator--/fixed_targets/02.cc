#include <fuzzer/FuzzedDataProvider.h>
#include <parallel_hashmap/phmap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Define a hash map
    phmap::flat_hash_map<std::string, std::string> map;

    // Populate the map with random key-value pairs
    while (stream.remaining_bytes() > 0) {
        std::string key = stream.ConsumeRandomLengthString();
        std::string value = stream.ConsumeRandomLengthString();
        map[key] = value;
    }

    // Get an iterator to the beginning of the map
    auto it = map.begin();

    // Call the operator++ on the iterator
    if (!map.empty()) {
        ++it;
    }

    return 0;
}