#include <hb.h>
#include <hb-ot.h>

int main() {
  hb_font_t *font = hb_font_create();
  hb_buffer_t *buffer = hb_buffer_create();
  hb_ot_shape_glyphs_closure(font, buffer, NULL, NULL);
  hb_font_destroy(font);
  hb_buffer_destroy(buffer);
  return 0;
}