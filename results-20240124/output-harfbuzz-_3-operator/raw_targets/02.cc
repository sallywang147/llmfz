 #include <hb-ot.h>
#include <hb-shape.h>
#include <hb-fuzzer.hh>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  alloc_state = _fuzzing_alloc_state(data, size);
  hb_blob_t *blob = hb_blob_create((const char *)data, size,
                                   HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);
  hb_shape_plan_t *plan = hb_shape_plan_create(font, nullptr, nullptr, 0);
  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, "Hello, world!", 13, 0, 13);
  hb_shape_plan_execute(plan, buffer, nullptr, 0);

  hb_glyph_info_t *info = hb_buffer_get_glyph_infos(buffer, nullptr);
  double x = 0;
  for (unsigned int i = 0; i < hb_buffer_get_length(buffer); i++)
  {
    x += hb_shape_justify::$_3{}.operator(&info[i], x);
  }

  hb_buffer_destroy(buffer);
  hb_shape_plan_destroy(plan);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);
  return 0;
}