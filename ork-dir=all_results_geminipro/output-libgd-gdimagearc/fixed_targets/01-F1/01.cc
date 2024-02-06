#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "gd.h"
#include "gdfontg.h"
#include "gdfontl.h"
#include "gdfontmb.h"
#include "gdfonts.h"
#include "gdfontt.h"

extern "C" {
#include <gd.h>
#include <gdfontg.h>
#include <gdfontl.h>
#include <gdfontmb.h>
#include <gdfonts.h>
#include <gdfontt.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();
  gdImagePtr slate_image = gdImageCreateTrueColor(slate_width, slate_height);
  if (slate_image == nullptr) {
    return 0;
  }

  const int cx = stream.ConsumeIntegral<int>();
  const int cy = stream.ConsumeIntegral<int>();
  const int w = stream.ConsumeIntegral<int>();
  const int h = stream.ConsumeIntegral<int>();
  const int s = stream.ConsumeIntegral<int>();
  const int e = stream.ConsumeIntegral<int>();
  const int color = stream.ConsumeIntegral<int>();

  gdImageArc(slate_image, cx, cy, w, h, s, e, color);
  gdImageDestroy(slate_image);
  return 0;
}
```

The issue was that the `gd.h` and other related headers were not wrapped in `extern "C" {}`. This caused the linker to not be able to find the definitions of the functions and data structures declared in these headers. To fix this, we wrapped the `#include` directives for these headers in `extern "C" {}`.