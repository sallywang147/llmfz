 #include <assert.h>
#include <stdlib.h>

#include <hb-ot.h>

#include "hb-fuzzer.hh"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  alloc_state = _fuzzing_alloc_state(data, size);

  hb_blob_t *blob = hb_blob_create((const char *)data, size, HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  unsigned num_coords = 0;
  if (size)
    num_coords = data[size - 1];
  num_coords = hb_ot_var_get_axis_count(face) > num_coords ? num_coords : hb_ot_var_get_axis_count(face);
  int *coords = (int *)calloc(num_coords, sizeof(int));
  if (size > num_coords + 1)
    for (unsigned i = 0; i < num_coords; ++i)
      coords[i] = ((int)data[size - num_coords + i - 1] - 128) * 10;
  hb_font_set_var_coords_normalized(font, coords, num_coords);
  free(coords);

  hb_buffer_t *buf = hb_buffer_create();
  hb_buffer_add_utf8(buf, "Hello, World!", 13, 0, 13);

  hb_feature_t features[1];
  features[0].tag = HB_TAG('a','a','l','t');
  features[0].value = 1;
  features[0].start = 0;
  features[0].end = 13;

  hb_shape(font, buf, features, 1, nullptr, 0);

  hb_glyph_info_t *info = hb_buffer_get_glyph_infos(buf, nullptr);
  for (unsigned i = 0; i < hb_buffer_get_length(buf); i++) {
    double x1, y1, x2, y2, x3, y3, x4, y4;
    hb_font_get_glyph_contour_point(font, info[i].codepoint, 0, &x1, &y1);
    hb_font_get_glyph_contour_point(font, info[i].codepoint, 1, &x2, &y2);
    hb_font_get_glyph_contour_point(font, info[i].codepoint, 2, &x3, &y3);
    hb_font_get_glyph_contour_point(font, info[i].codepoint, 3, &x4, &y4);
    double solve_itp<(lambda at ../../src/harfbuzz/src/hb-shape.cc:405:12)>(from /work/build/../../src/harfbuzz/src/hbshape.cc:405 DW_TAG_class_type Composite type, x1, y1, x2, y2, x3, y3, x4, y4);
  }

  hb_buffer_destroy(buf);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);
  return 0;
}