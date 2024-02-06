#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "hb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  hb_buffer_t* buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, text.c_str(), text.size(), 0, text.size());

  const int num_features = stream.ConsumeIntegral<int>();
  std::vector<hb_glyph_extents_t> features(num_features);
  for (int i = 0; i < num_features; ++i) {
    features[i].x_bearing = stream.ConsumeIntegral<int>();
    features[i].y_bearing = stream.ConsumeIntegral<int>();
    features[i].width = stream.ConsumeIntegral<int>();
    features[i].height = stream.ConsumeIntegral<int>();
  }

  const int num_shapers = stream.ConsumeIntegralInRange<int>(0, 10);
  std::vector<const char*> shaper_list(num_shapers);  // Fix: Change the type to std::vector<const char*>
  for (int i = 0; i < num_shapers; ++i) {
    shaper_list[i] = stream.ConsumeBytesAsString(
        stream.ConsumeIntegralInRange<size_t>(0, 10)).c_str();
  }

  const float min_target_advance = stream.ConsumeFloatingPoint<float>();
  const float max_target_advance = stream.ConsumeFloatingPoint<float>();
  float advance;
  int var_tag;
  float var_value;
  hb_shape_justify(nullptr, buffer, features.data(), num_features,
                   shaper_list.data(), min_target_advance, max_target_advance,
                   &advance, &var_tag, &var_value);
  hb_buffer_destroy(buffer);
  return 0;
}
```

The issue in the original code was that the type of `shaper_list` was incorrect. It was declared as `std::vector<std::string>`, which is not compatible with the `hb_shape_justify` function, which expects a `std::vector<const char*>`.

To fix this, the type of `shaper_list` was changed to `std::vector<const char*>`. This ensures that the `hb_shape_justify` function can correctly access the shaper names.