#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "hb.h"
#include "hb-ot.h"

extern "C" {
#include "hb-glib.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_font_t* font = hb_font_create();
  hb_buffer_t* buffer = hb_buffer_create();
  hb_set_t* glyphs = hb_set_create();

  const std::string text = stream.ConsumeRemainingBytesAsString();
  hb_buffer_add_utf8(buffer, text.c_str(), text.size(), 0, text.size());

  hb_shape(font, buffer, nullptr, 0);
  hb_ot_shape_glyphs_closure(font, buffer, nullptr, 0, glyphs);

  hb_font_destroy(font);
  hb_buffer_destroy(buffer);
  hb_set_destroy(glyphs);

  return 0;
}
```

Changes made:

- Removed `hb_feature_t* features = nullptr;` and `int num_features = 0;` lines. These are not needed because `hb_shape` will automatically handle feature application.
- Added `hb_shape` function call before `hb_ot_shape_glyphs_closure`. This is necessary because `hb_ot_shape_glyphs_closure` requires the glyphs to be shaped before it can be used.