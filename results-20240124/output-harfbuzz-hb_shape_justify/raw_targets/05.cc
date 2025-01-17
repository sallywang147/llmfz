 #include <hb-fuzzer.hh>

#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  alloc_state = _fuzzing_alloc_state (data, size);

  hb_blob_t *blob = hb_blob_create ((const char *) data, size,
				    HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create (blob, 0);
  hb_font_t *font = hb_font_create (face);

  unsigned num_coords = 0;
  if (size) num_coords = data[size - 1];
  num_coords = hb_ot_var_get_axis_count (face) > num_coords ? num_coords : hb_ot_var_get_axis_count (face);
  int *coords = (int *) calloc (num_coords, sizeof (int));
  if (size > num_coords + 1)
    for (unsigned i = 0; i < num_coords; ++i)
      coords[i] = ((int) data[size - num_coords + i - 1] - 128) * 10;
  hb_font_set_var_coords_normalized (font, coords, num_coords);
  free (coords);

  hb_buffer_t *buffer = hb_buffer_create ();
  hb_buffer_add_utf8 (buffer, (const char *) data, size, 0, size);

  hb_glyph_extents_t *features = nullptr;
  int num_features = 0;
  char **shaper_list = nullptr;
  float min_target_advance = 0.f;
  float max_target_advance = 0.f;
  float advance = 0.f;
  int var_tag = 0;
  float var_value = 0.f;

  hb_shape_justify (font, buffer, features, num_features, shaper_list, min_target_advance, max_target_advance, &advance, &var_tag, &var_value);

  hb_buffer_destroy (buffer);
  hb_font_destroy (font);
  hb_face_destroy (face);
  hb_blob_destroy (blob);

  return 0;
}