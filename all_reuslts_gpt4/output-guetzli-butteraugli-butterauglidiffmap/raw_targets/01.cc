#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<butteraugli::Image> images;
  while (stream.remaining_bytes() > 0) {
    size_t xsize = stream.ConsumeIntegralInRange<size_t>(1, 100);
    size_t ysize = stream.ConsumeIntegralInRange<size_t>(1, 100);
    butteraugli::Image image(xsize, ysize);
    for (size_t y = 0; y < ysize; ++y) {
      for (size_t x = 0; x < xsize; ++x) {
        for (int c = 0; c < 3; ++c) {
          image.Row(y)[3 * x + c] = stream.ConsumeFloatingPoint<double>();
        }
      }
    }
    images.push_back(image);
    if (images.size() == 2) {
      std::vector<std::vector<float>> diffmap;
      butteraugli::ButteraugliDiffmap(images[0], images[1], &diffmap);
      images.clear();
    }
  }
  return 0;
}