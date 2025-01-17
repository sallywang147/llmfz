#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <hb.h>
#include <hb-ot.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  hb_font_t *font = hb_font_create();
  hb_buffer_t *buffer = hb_buffer_create();
  hb_feature_t *features = (hb_feature_t *)malloc(sizeof(hb_feature_t) * 1);
  features[0].tag = HB_TAG('a', 'a', 'a', 'a');
  features[0].value = 1;
  hb_set_t *glyphs = hb_set_create();
  hb_ot_shape_glyphs_closure(font, buffer, features, 1, glyphs);
  hb_font_destroy(font);
  hb_buffer_destroy(buffer);
  free(features);
  hb_set_destroy(glyphs);
  return 0;
}