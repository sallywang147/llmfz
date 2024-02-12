#include <stdint.h>
#include <string>
#include <vector>

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string jpeg_data(reinterpret_cast<const char*>(data), size);

  // Ignore large images, to prevent timeouts.
  butteraugli::JPEGData jpg_header;
  if (!butteraugli::ReadJpeg(data, size, butteraugli::JPEG_READ_HEADER, &jpg_header)) {
    return 0;
  }
  static constexpr int kMaxPixels = 10000;
  if (static_cast<int64_t>(jpg_header.width) * jpg_header.height > kMaxPixels) {
    return 0;
  }

  // TODO(robryk): Use nondefault parameters.
  butteraugli::Params params;
  std::vector<butteraugli::ImageF> images;
  std::vector<butteraugli::ImageF> diffs;
  butteraugli::Image img;
  double score;
  butteraugli::ButteraugliInterface(images, diffs, &img, &score);
  // TODO(robryk): Verify output distance if ButteraugliInterface() succeeded.
  return 0;
}