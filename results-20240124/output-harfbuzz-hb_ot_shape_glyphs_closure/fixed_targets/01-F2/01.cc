#include "hb-fuzzer.hh"

extern "C" {
#include <hb.h>
#include <hb-ot.h>
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  hb_font_t *font = hb_font_create();
  hb_buffer_t *buffer = hb_buffer_create();
  hb_feature_t *features = nullptr;
  int num_features = 0;
  hb_set_t *glyphs = hb_set_create();

  hb_buffer_add(buffer, data, size);

  hb_ot_shape_glyphs_closure(font, buffer, features, num_features, glyphs);

  hb_font_destroy(font);
  hb_buffer_destroy(buffer);
  hb_set_destroy(glyphs);
}