#include <fuzzer/FuzzedDataProvider.h>
#include <gd.h>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new image with random dimensions
  int width = stream.ConsumeIntegralInRange<int>(1, 500);
  int height = stream.ConsumeIntegralInRange<int>(1, 500);
  gdImagePtr im = gdImageCreate(width, height);

  // Consume data for the gdImageArc parameters
  int cx = stream.ConsumeIntegral<int>();
  int cy = stream.ConsumeIntegral<int>();
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();
  int s = stream.ConsumeIntegral<int>();
  int e = stream.ConsumeIntegral<int>();
  int color = stream.ConsumeIntegral<int>();

  // Call the target function
  gdImageArc(im, cx, cy, w, h, s, e, color);

  // Clean up
  gdImageDestroy(im);

  return 0;
}