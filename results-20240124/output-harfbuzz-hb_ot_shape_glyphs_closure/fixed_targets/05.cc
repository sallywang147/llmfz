#include <assert.h>
#include <stdlib.h>

extern "C" {
#include <hb-ot.h>
}

#include "hb-fuzzer.hh"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  alloc_state_t alloc_state = _fuzzing_alloc_state(data, size);

  hb_blob_t* blob = hb_blob_create((const char*)data, size,
                                   HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t* face = hb_face_create(blob, 0);
  hb_font_t* font = hb_font_create(face);

  unsigned num_coords = 0;
  if (size) num_coords = data[size - 1];
  num_coords = hb_ot_var_get_axis_count(face) > num_coords ? num_coords : hb_ot_var_get_axis_count(face);
  int* coords = (int*)calloc(num_coords, sizeof(int));
  if (size > num_coords + 1)
    for (unsigned i = 0; i < num_coords; ++i)
      coords[i] = ((int)data[size - num_coords + i - 1] - 128) * 10;
  hb_font_set_var_coords_normalized(font, coords, num_coords);
  free(coords);

  unsigned glyph_count = hb_face_get_glyph_count(face);
  glyph_count = glyph_count > 16 ? 16 : glyph_count;

  hb_set_t* glyphs = hb_set_create();
  for (unsigned gid = 0; gid < glyph_count; ++gid)
    hb_set_add(glyphs, gid);

  unsigned num_features = 0;
  if (size) num_features = data[size - 1];
  num_features = hb_ot_layout_table_get_feature_count(face) > num_features ? num_features : hb_ot_layout_table_get_feature_count(face);
  hb_feature_t* features = (hb_feature_t*)calloc(num_features, sizeof(hb_feature_t));
  if (size > num_features + 1)
    for (unsigned i = 0; i < num_features; ++i) {
      features[i].tag = HB_TAG(data[size - num_features + i - 1], data[size - num_features + i - 2], data[size - num_features + i - 3], data[size - num_features + i - 4]);
      features[i].value = 1;
      features[i].start = 0;
      features[i].end = (unsigned int)-1;
    }

  hb_buffer_t* buffer = hb_buffer_create();
  hb_ot_shape_glyphs_closure(font, buffer, features, num_features, glyphs);

  hb_buffer_destroy(buffer);
  hb_set_destroy(glyphs);
  free(features);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);
  return 0;
}