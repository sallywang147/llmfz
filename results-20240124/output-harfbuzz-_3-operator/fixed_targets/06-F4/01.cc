#include <hb.h>
#include <hb-ot.h>

extern "C" {
#include <hb-shape.h>
}

int main() {
  hb_font_t *font = hb_font_create();
  hb_buffer_t *buffer = hb_buffer_create();
  hb_shape(font, buffer, nullptr, 0);
  hb_shape_justify(buffer, 0.5);
  hb_font_destroy(font);
  hb_buffer_destroy(buffer);
  return 0;
}