#include <hb.h>
#include <hb-ot.h>
#include <hb-ft.h>

extern "C" {
#include <hb-shape.h>
#include <hb-shape-justify.h> // Include the header that declares the function `hb_shape_justify::$_3::operator`
}

int main() {
  hb_font_t *font = hb_font_create();
  hb_buffer_t *buffer = hb_buffer_create();
  hb_shape(font, buffer, NULL, 0);
  hb_shape_justify(font, buffer, NULL);

  // Use the justified buffer here...

  hb_buffer_destroy(buffer);
  hb_font_destroy(font);

  return 0;
}