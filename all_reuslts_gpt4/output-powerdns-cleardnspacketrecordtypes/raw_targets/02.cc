#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

extern "C" void clearDNSPacketRecordTypes(std::vector<int>*, std::unordered_map<int, std::vector<int>>*);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<int> vec;
  std::unordered_map<int, std::vector<int>> umap;

  while (stream.remaining_bytes() > 0) {
    int key = stream.ConsumeIntegral<int>();
    size_t vec_size = stream.ConsumeIntegralInRange<size_t>(0, 10);

    std::vector<int> value;
    for (size_t i = 0; i < vec_size; i++) {
      int element = stream.ConsumeIntegral<int>();
      value.push_back(element);
      vec.push_back(element);
    }

    umap.insert({key, value});
  }

  clearDNSPacketRecordTypes(&vec, &umap);

  return 0;
}