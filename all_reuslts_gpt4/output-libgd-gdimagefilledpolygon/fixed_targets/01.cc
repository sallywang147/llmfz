#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "gd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);
  
  // Create an image
  gdImagePtr im = gdImageCreateTrueColor(100, 100);
  if (!im) {
    return 0;
  }

  // Generate color
  int c = stream.ConsumeIntegral<int>();

  // Consume data for points
  std::vector<gdPoint> points;
  while (stream.remaining_bytes() > sizeof(gdPoint)) {
    gdPoint point;
    point.x = stream.ConsumeIntegral<int>();
    point.y = stream.ConsumeIntegral<int>();
    points.push_back(point);
  }

  // Call the function to fuzz
  gdImageFilledPolygon(im, points.data(), points.size(), c);

  // Clean up
  gdImageDestroy(im);

  return 0;
}