#include <hb-ot-shape.h>

extern "C" {
#include <harfbuzz/hb-shape.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  hb_font_t *font = hb_font_create();
  hb_buffer_t *buffer = hb_buffer_create();
  hb_glyph_extents_t features[1];
  char *shaper_list = nullptr;
  float min_target_advance = 0.0f;
  float max_target_advance = 0.0f;
  float advance = 0.0f;
  int var_tag = 0;
  float var_value = 0.0f;

  hb_shape_justify(font, buffer, features, 1, &shaper_list, min_target_advance, max_target_advance, &advance, &var_tag, &var_value);

  hb_font_destroy(font);
  hb_buffer_destroy(buffer);

  return 0;
}