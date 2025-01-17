#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "hb-ot.h"

struct ASS_Rect {
  int x, y;
  int w, h;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  hb_blob_t *blob = hb_blob_create(reinterpret_cast<const char*>(data), size,
                                   HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, reinterpret_cast<const char*>(data), size, 0, size);

  FuzzedDataProvider provider(data, size);

  int num_features = provider.ConsumeIntegralInRange<int>(0, 10);
  std::vector<ASS_Rect> features(num_features);
  for (int i = 0; i < num_features; i++) {
    features[i].x = provider.ConsumeIntegral<int>();
    features[i].y = provider.ConsumeIntegral<int>();
    features[i].w = provider.ConsumeIntegral<int>();
    features[i].h = provider.ConsumeIntegral<int>();
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