#include <stdint.h>

extern "C" {
#include "guetzli/jpeg_data.h"
#include "guetzli/jpeg_data_writer.h"
#include "guetzli/processor.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string jpeg_data(reinterpret_cast<const char *>(data), size);

  // Ignore large images, to prevent timeouts.
  guetzli::JPEGData jpg_header;
  if (!guetzli::ReadJpeg(data, size, guetzli::JPEG_READ_HEADER, &jpg_header)) {
    return 0;
  }
  static constexpr int kMaxPixels = 10000;
  if (static_cast<int64_t>(jpg_header.width) * jpg_header.height > kMaxPixels) {
    return 0;
  }

  guetzli::JPEGData jpg;
  if (!guetzli::ReadJpeg(data, size, guetzli::JPEG_READ_ALL, &jpg)) {
    return 0;
  }

  // TODO(robryk): Use nondefault parameters.
  guetzli::Params params;
  guetzli::Process(params, nullptr, jpeg_data, nullptr);

  std::vector<guetzli::HuffmanCode> codes;
  std::vector<uint8_t> bits;
  guetzli::BuildSequentialHuffmanCodes(&jpg, &codes, &bits);

  // TODO(robryk): Verify the output somehow.
  return 0;
}