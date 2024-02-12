#include <stdint.h>
#include <stddef.h>
#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  butteraugli::Image img;
  if (!butteraugli::LoadPng(&img, data, size)) {
    return 0;
  }

  // Ignore large images, to prevent timeouts.
  static constexpr int kMaxPixels = 10000;
  if (static_cast<int64_t>(img.width) * img.height > kMaxPixels) {
    return 0;
  }

  butteraugli::ButteraugliDiffmap(nullptr, nullptr, &img);
  return 0;
}