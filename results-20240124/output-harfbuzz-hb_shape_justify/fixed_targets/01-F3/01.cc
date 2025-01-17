#include <hb.h>

extern "C" {
#include <hb-ft.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  hb_font_t *font = hb_ft_font_create();
  hb_buffer_t *buffer = hb_buffer_create();
  hb_glyph_extents_t features[1];
  int num_features = 1;
  char *shaper_list[] = {"default"};
  float min_target_advance = 0.0;
  float max_target_advance = 0.0;
  float advance;
  int var_tag;
  float var_value;

  hb_shape_justify(font, buffer, features, num_features, shaper_list, min_target_advance, max_target_advance, &advance, &var_tag, &var_value);

  hb_font_destroy(font);
  hb_buffer_destroy(buffer);

  return 0;
}