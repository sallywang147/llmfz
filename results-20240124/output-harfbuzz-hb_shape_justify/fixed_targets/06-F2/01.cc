#include <hb.h>
#include <hb-ot.h>
#include <stdlib.h>

extern "C" {
#include "hb-ot-color.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  hb_font_t *font = hb_font_create();
  hb_buffer_t *buffer = hb_buffer_create();
  hb_glyph_extents_t features;
  int num_features = 0;
  char **shaper_list = NULL;
  float min_target_advance = 0.0f;
  float max_target_advance = 0.0f;
  float *advance = NULL;
  int *var_tag = NULL;
  float *var_value = NULL;

  hb_shape_justify(font, buffer, &features, num_features, shaper_list, min_target_advance, max_target_advance, advance, var_tag, var_value);

  hb_font_destroy(font);
  hb_buffer_destroy(buffer);

  return 0;
}