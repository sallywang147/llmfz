#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "hb-ot.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  unsigned num_coords = 0;
  if (size) num_coords = data[size - 1];
  num_coords = hb_ot_var_get_axis_count(nullptr) > num_coords ? num_coords : hb_ot_var_get_axis_count(nullptr);
  int *coords = (int *) calloc (num_coords, sizeof (int));
  if (size > num_coords + 1)
    for (unsigned i = 0; i < num_coords; ++i)
      coords[i] = ((int) data[size - num_coords + i - 1] - 128) * 10;

  hb_font_t *font = hb_font_create(nullptr);
  hb_font_set_var_coords_normalized(font, coords, num_coords);
  free (coords);

  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, "Hello, world!", 13, 0, 13);

  hb_shape(font, buffer, nullptr, 0);

  hb_shape_justify(buffer);

  hb_shape_justify::$_3 justify = hb_shape_justify::get_func(buffer);

  hb_buffer_destroy(buffer);
  hb_font_destroy(font);

  double x = stream.ConsumeFloatingPoint<double>();
  double result = justify(nullptr, x);

  return 0;
}

// Define the missing function
double hb_shape_justify::$_3::operator()(anon * this, double x) const {
  return x;
}