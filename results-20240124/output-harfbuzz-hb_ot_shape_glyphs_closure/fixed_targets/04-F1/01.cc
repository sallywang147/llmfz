#include <assert.h>
#include <stdlib.h>

#include <hb-ot.h>

#include "hb-fuzzer.hh"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  alloc_state = _fuzzing_alloc_state(data, size);

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

  hb_buffer_t* buffer = hb_buffer_create();
  hb_buffer_add_glyphs(buffer, glyphs, 0, -1);

  hb_ot_shape_glyphs_closure(font, buffer, nullptr, 0, glyphs);

  hb_buffer_destroy(buffer);
  hb_set_destroy(glyphs);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);
  return 0;
}