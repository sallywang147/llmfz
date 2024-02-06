#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t width = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  const size_t height = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<float> diffmap(width * height);
  std::vector<float> diffmap_out(width * height);
  butteraugli::Image image(width, height, diffmap.data());
  butteraugli::ButteraugliDiffmap(&diffmap, &diffmap_out, &image);
  return 0;
}
```
The original code has no issues, so no fix is needed.