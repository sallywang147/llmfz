#include <fuzzer/FuzzedDataProvider.h>
#include <hb.h>
#include <hb-ot.h>

struct ASS_Rect {
  int x1, y1, x2, y2;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_blob_t *blob = hb_blob_create((const char *)data, size, HB_MEMORY_MODE_READONLY, NULL, NULL);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, (const char *)data, size, 0, -1);
  hb_buffer_guess_segment_properties(buffer);

  int num_features = stream.ConsumeIntegralInRange<int>(0, 10);
  std::vector<ASS_Rect> features(num_features);
  for (int i = 0; i < num_features; ++i) {
    features[i].x1 = stream.ConsumeIntegral<int>();
    features[i].y1 = stream.ConsumeIntegral<int>();
    features[i].x2 = stream.ConsumeIntegral<int>();
    features[i].y2 = stream.ConsumeIntegral<int>();
  }

  hb_set_t *glyphs = hb_set_create();

  hb_ot_shape_glyphs_closure(font, buffer, features.data(), num_features, glyphs);

  hb_set_destroy(glyphs);
  hb_buffer_destroy(buffer);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return 0;
}