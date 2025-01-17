#include <hb.h>
#include <hb-ot.h>

extern "C" {
#include <hb-shape.h>
}

int main() {
  hb_shape_t *shape = hb_shape_create();
  hb_shape_set_justify(shape, HB_SHAPE_JUSTIFY_FULL);
  hb_shape_execute(shape);
  hb_shape_destroy(shape);
  return 0;
}