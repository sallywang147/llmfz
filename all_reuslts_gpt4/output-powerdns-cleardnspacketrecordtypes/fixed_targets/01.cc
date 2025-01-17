#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<int> vec;
  std::unordered_map<int, int> umap;

  // Populate vector and unordered_map with random data
  while (stream.remaining_bytes() > 0) {
    int key = stream.ConsumeIntegral<int>();
    int value = stream.ConsumeIntegral<int>();
    vec.push_back(key);
    umap[key] = value;
  }

  clearDNSPacketRecordTypes(&vec, &umap);

  return 0;
}