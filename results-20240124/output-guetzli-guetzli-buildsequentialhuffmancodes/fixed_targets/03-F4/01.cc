#include <stdint.h>
#include "guetzli/jpeg_data.h"
#include "guetzli/jpeg_data_reader.h"
#include "guetzli/processor.h"
#include "guetzli/quality.h"

#include "guetzli/huffman_codes.h"

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

  // TODO(robryk): Use nondefault parameters.
  guetzli::Params params;
  std::string jpeg_out;
  (void)guetzli::Process(params, nullptr, jpeg_data, &jpeg_out);
  // TODO(robryk): Verify output distance if Process() succeeded.

  // Read the JPEG data.
  guetzli::JPEGData jpg;
  if (!guetzli::ReadJpeg(jpeg_out, guetzli::JPEG_READ_ALL, &jpg)) {
    return 0;
  }

  // Build the Huffman codes.
  std::vector<guetzli::HuffmanCode> dc_codes;
  std::vector<guetzli::HuffmanCode> ac_codes;
  guetzli::BuildSequentialHuffmanCodes(&jpg, &dc_codes, &ac_codes);

  return 0;
}