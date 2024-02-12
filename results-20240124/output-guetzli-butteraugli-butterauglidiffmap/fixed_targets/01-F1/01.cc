#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate random image dimensions.
  const int width = provider.ConsumeIntegralInRange<int>(1, 100);
  const int height = provider.ConsumeIntegralInRange<int>(1, 100);

  // Generate random pixel values.
  std::vector<uint8_t> pixel_data(width * height * 3);
  for (uint8_t &pixel : pixel_data) {
    pixel = provider.ConsumeIntegral<uint8_t>();
  }

  // Create butteraugli::Image objects.
  butteraugli::Image img1(width, height, pixel_data);
  butteraugli::Image img2(width, height, pixel_data);

  // Create empty vectors for the diffmap and score.
  std::vector<float> diffmap;
  std::vector<float> score;

  // Call butteraugli::ButteraugliDiffmap.
  butteraugli::ButteraugliDiffmap(&diffmap, &score, &img1, &img2);

  return 0;
}