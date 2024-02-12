 #include <stdint.h>
#include "guetzli/jpeg_data.h"
#include "guetzli/jpeg_data_writer.h"
#include "guetzli/processor.h"

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
  guetzli::JPEGData jpg_data;
  std::string jpeg_out;
  (void)guetzli::Process(params, nullptr, jpeg_data, &jpeg_out);

  // TODO(robryk): Verify output distance if Process() succeeded.
  std::vector<guetzli::HuffmanCode> dc_codes;
  std::vector<guetzli::HuffmanCode> ac_codes;
  guetzli::BuildSequentialHuffmanCodes(&jpg_data, &dc_codes, &ac_codes);
  return 0;
}