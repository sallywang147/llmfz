#include <stdint.h>
#include "guetzli/jpeg_data.h"
#include "guetzli/jpeg_data_reader.h"
#include "guetzli/output_image.h"
#include "guetzli/processor.h"
#include "guetzli/quality.h"

#include "guetzli/build_sequential_huffman_codes.h"

extern "C" {
#include "guetzli/output_image.h"
#include "guetzli/build_sequential_huffman_codes.h"
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

  // Read the entire JPEG file.
  if (!guetzli::ReadJpeg(data, size, guetzli::JPEG_READ_ALL, &jpg_header)) {
    return 0;
  }

  // TODO(robryk): Use nondefault parameters.
  guetzli::Params params;
  std::vector<uint8_t> huffman_codes;
  std::vector<uint8_t> huffman_bits;
  guetzli::BuildSequentialHuffmanCodes(&jpg_header, &huffman_codes,
                                      &huffman_bits);
  // TODO(robryk): Verify output distance if BuildSequentialHuffmanCodes()
  // succeeded.
  return 0;
}