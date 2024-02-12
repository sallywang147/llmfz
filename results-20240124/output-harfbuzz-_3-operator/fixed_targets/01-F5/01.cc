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

  // Call the function that was not called by the fuzz target
  double x = 0.5;
  hb_shape_justify(shape, x);

  return 0;
}