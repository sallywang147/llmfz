#include <fuzzer/FuzzedDataProvider.h>
#include <gd.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new image
  int width = 100;
  int height = 100;
  gdImagePtr im = gdImageCreateTrueColor(width, height);
  if (im == NULL) {
    return 0;
  }

  // Consume data to create an array of points
  int num_points = stream.ConsumeIntegralInRange<int>(0, 100);
  std::vector<gdPoint> points(num_points);
  for (int i = 0; i < num_points; i++) {
    points[i].x = stream.ConsumeIntegralInRange<int>(0, width);
    points[i].y = stream.ConsumeIntegralInRange<int>(0, height);
  }

  // Consume data to create a color
  int color = stream.ConsumeIntegral<int>();

  // Call the target function
  gdImageFilledPolygon(im, points.data(), num_points, color);

  // Clean up
  gdImageDestroy(im);

  return 0;
}