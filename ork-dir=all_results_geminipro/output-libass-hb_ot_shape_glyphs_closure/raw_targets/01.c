#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "hb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_font_t* font = hb_font_create();
  hb_buffer_t* buffer = hb_buffer_create();

  const std::string text = stream.ConsumeRemainingBytesAsString();
  hb_buffer_add_utf8(buffer, text.c_str(), text.size(), 0, text.size());

  const int num_features = stream.ConsumeIntegralInRange<int>(0, 10);
  ASS_Rect* features =
      static_cast<ASS_Rect*>(calloc(num_features, sizeof(ASS_Rect)));
  for (int i = 0; i < num_features; i++) {
    features[i].x = stream.ConsumeIntegral<int>();
    features[i].y = stream.ConsumeIntegral<int>();
    features[i].w = stream.ConsumeIntegral<int>();
    features[i].h = stream.ConsumeIntegral<int>();
  }

  hb_set_t* glyphs = hb_set_create();

  hb_ot_shape_glyphs_closure(font, buffer, features, num_features, glyphs);

  hb_set_destroy(glyphs);
  free(features);
  hb_buffer_destroy(buffer);
  hb_font_destroy(font);

  return 0;
}