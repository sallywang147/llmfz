#include <assert.h>
#include <stdlib.h>

#include <hb-ot.h>

#include "hb-fuzzer.hh"

/* Similar to test-ot-face.c's #test_font() */
static void misc_calls_for_gid (hb_face_t *face, hb_font_t *font, hb_set_t *set, hb_codepoint_t cp)
{
  /* Other gid specific misc calls */
  hb_face_collect_variation_unicodes (face, cp, set);

  hb_codepoint_t g;
  hb_font_get_nominal_glyph (font, cp, &g);
  hb_font_get_variation_glyph (font, cp, cp, &g);
  hb_font_get_glyph_h_advance (font, cp);
  hb_font_get_glyph_v_advance (font, cp);
  hb_position_t x, y;
  hb_font_get_glyph_h_origin (font, cp, &x, &y);
  hb_font_get_glyph_v_origin (font, cp, &x, &y);
  hb_font_get_glyph_contour_point (font, cp, 0, &x, &y);
  char buf[64];
  hb_font_get_glyph_name (font, cp, buf, sizeof (buf));

  hb_ot_color_palette_get_name_id (face, cp);
  hb_ot_color_palette_color_get_name_id (face, cp);
  hb_ot_color_palette_get_flags (face, cp);
  hb_ot_color_palette_get_colors (face, cp, 0, nullptr, nullptr);
  hb_ot_color_glyph_get_layers (face, cp, 0, nullptr, nullptr);
  hb_blob_destroy (hb_ot_color_glyph_reference_svg (font, cp));
  hb_blob_destroy (hb_ot_color_glyph_reference_png (face, cp));

  hb_ot_layout_get_ligature_carets (font, HB_DIRECTION_LTR, cp, 0, nullptr, nullptr);

  hb_ot_math_get_glyph_italics_correction (font, cp);
  hb_ot_math_get_glyph_top_accent_attachment (font, cp);
  hb_ot_math_is_glyph_extended_shape (face, cp);
  hb_ot_math_get_glyph_kerning (font, cp, HB_OT_MATH_KERN_BOTTOM_RIGHT, 0);
  hb_ot_math_get_glyph_variants (font, cp, HB_DIRECTION_TTB, 0, nullptr, nullptr);
  hb_ot_math_get_glyph_assembly (font, cp, HB_DIRECTION_BTT, 0, nullptr, nullptr, nullptr);
}

extern "C" int LLVMFuzzerTestOneInput (const uint8_t *data, size_t size)
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

  unsigned glyph_count = hb_face_get_glyph_count (face);
  glyph_count = glyph_count > 16 ? 16 : glyph_count;

  hb_buffer_t *buffer = hb_buffer_create ();

  hb_glyph_extents_t *features = (hb_glyph_extents_t *) calloc (glyph_count, sizeof (hb_glyph_extents_t));
  int num_features = glyph_count;
  for (unsigned i = 0; i < glyph_count; i++) {
    features[i].x_bearing = rand () % 100;
    features[i].y_bearing = rand () % 100;
    features[i].width = rand () % 100;
    features[i].height = rand () % 100;
  }

  char **shaper_list = (char **) calloc (glyph_count, sizeof (char *));
  for (unsigned i = 0; i < glyph_count; i++) {
    shaper_list[i] = (char *) calloc (10, sizeof (char));
    sprintf (shaper_list[i], "shaper%d", i);
  }

  float min_target_advance = rand () % 100;
  float max_target_advance = rand () % 100;
  float advance;
  int var_tag;
  float var_value;

  int ret = hb_shape_justify (font, buffer, features, num_features, shaper_list, min_target_advance, max_target_advance, &advance, &var_tag, &var_value);
  assert (ret != -1);

  hb_buffer_destroy (buffer);
  free (features);
  for (unsigned i = 0; i < glyph_count; i++)
    free (shaper_list[i]);
  free (shaper_list);

  hb_font_destroy (font);
  hb_face_destroy (face);
  hb_blob_destroy (blob);
  return 0;
}