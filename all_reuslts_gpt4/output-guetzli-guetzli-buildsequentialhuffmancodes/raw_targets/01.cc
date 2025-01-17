#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "guetzli/jpeg_data.h"
#include "guetzli/huffman_encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  guetzli::JPEGData jpeg_data;
  std::vector<guetzli::HuffmanCode> codes;
  std::vector<int> counts;

  size_t codes_size = provider.ConsumeIntegralInRange<size_t>(0, size / 2);
  for (size_t i = 0; i < codes_size; ++i) {
    guetzli::HuffmanCode code;
    code.bits = provider.ConsumeIntegral<uint8_t>();
    code.value = provider.ConsumeIntegral<uint16_t>();
    codes.push_back(code);
  }

  size_t counts_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  for (size_t i = 0; i < counts_size; ++i) {
    counts.push_back(provider.ConsumeIntegral<int>());
  }

  guetzli::BuildSequentialHuffmanCodes(&jpeg_data, &codes, &counts);

  return 0;
}