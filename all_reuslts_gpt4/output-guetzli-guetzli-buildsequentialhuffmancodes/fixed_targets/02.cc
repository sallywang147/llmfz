#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "guetzli/jpeg_data.h"
#include "guetzli/processor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  guetzli::JPEGData jpeg_data;
  std::vector<uint8_t> entropy_codes;
  std::vector<uint8_t> bit_lengths;

  // Fill the entropy_codes and bit_lengths vectors with data from the fuzzer.
  while (stream.remaining_bytes() > 0) {
    entropy_codes.push_back(stream.ConsumeIntegral<uint8_t>());
    bit_lengths.push_back(stream.ConsumeIntegral<uint8_t>());
  }

  guetzli::BuildSequentialHuffmanCodes(&jpeg_data, &entropy_codes, &bit_lengths);

  return 0;
}