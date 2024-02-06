#include <stdint.h>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" {
#include "butteraugli/butteraugli_interface.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Ignore large images, to prevent timeouts.
  if (size > 1 << 20) {
    return 0;
  }

  // TODO(robryk): Use nondefault parameters.
  butteraugli::ButteraugliParams params;
  std::vector<uint8_t> input0(data, data + size);
  std::vector<uint8_t> input1(data, data + size);
  butteraugli::Image img0, img1;
  double distance;
  bool ok = butteraugli::ButteraugliInterface(&input0, &input1, &img0, &img1, &distance);
  (void)ok;
  return 0;
}
```

The issue is that the function `ButteraugliInterface` takes 5 arguments, but only 4 are passed to it. To fix this, add the `&img1` argument to the function call.