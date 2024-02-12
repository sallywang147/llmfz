#include <stdint.h>
#include "guetzli/jpeg_data.h"
#include "guetzli/jpeg_data_reader.h"
#include "guetzli/processor.h"

extern "C" {
#include "guetzli/huffman_codes.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string jpeg_data(reinterpret_cast<const char*>(data), size);

  // Ignore large images, to prevent timeouts.
  guetzli::JPEGData jpg_header;
  if (!guetzli::ReadJpeg(data, size, guetzli::JPEG_READ_HEADER, &jpg_header)) {
    return 0;
  }
  static constexpr int kMaxPixels = 10000;
  if (static_cast<int64_t>(jpg_header.width) * jpg_header.height > kMaxPixels) {
    return 0;
  }

  guetzli::JPEGData jpg_data;
  if (!guetzli::ReadJpeg(data, size, guetzli::JPEG_READ_ALL, &jpg_data)) {
    return 0;
  }

  std::vector<uint8_t> dc_codes;
  std::vector<uint8_t> ac_codes;
  guetzli::BuildSequentialHuffmanCodes(&jpg_data, &dc_codes, &ac_codes);
  return 0;
}