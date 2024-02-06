#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int width = stream.ConsumeIntegralInRange<int>(1, 1000);
  int height = stream.ConsumeIntegralInRange<int>(1, 1000);
  gdImagePtr im = gdImageCreateTrueColor(width, height);
  if (!im) {
    return 0;
  }

  int cx = stream.ConsumeIntegralInRange<int>(0, width);
  int cy = stream.ConsumeIntegralInRange<int>(0, height);
  int w = stream.ConsumeIntegralInRange<int>(0, width);
  int h = stream.ConsumeIntegralInRange<int>(0, height);
  int s = stream.ConsumeIntegralInRange<int>(0, 360);
  int e = stream.ConsumeIntegralInRange<int>(0, 360);
  int color = stream.ConsumeIntegral<int>();
  int style = stream.ConsumeIntegral<int>();

  gdImageFilledArc(im, cx, cy, w, h, s, e, color, style);

  gdImageDestroy(im);

  return 0;
}