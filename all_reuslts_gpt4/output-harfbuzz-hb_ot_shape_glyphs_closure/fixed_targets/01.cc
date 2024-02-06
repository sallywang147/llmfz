#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "hb-ot.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  hb_blob_t *blob = hb_blob_create((const char *)stream.data(), stream.size(), HB_MEMORY_MODE_READONLY, NULL, NULL);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, (const char *)stream.data(), stream.size(), 0, -1);
  
  hb_feature_t *features = NULL;
  int num_features = 0;
  if (stream.remaining_bytes() > 0) {
    num_features = stream.ConsumeIntegralInRange<int>(1, 10);
    features = new hb_feature_t[num_features];
    for (int i = 0; i < num_features; i++) {
      features[i].tag = stream.ConsumeIntegral<uint32_t>();
      features[i].value = stream.ConsumeIntegral<uint32_t>();
      features[i].start = stream.ConsumeIntegral<uint32_t>();
      features[i].end = stream.ConsumeIntegral<uint32_t>();
    }
  }

  hb_set_t *glyphs = hb_set_create();

  hb_ot_shape_glyphs_closure(font, buffer, features, num_features, glyphs);

  hb_set_destroy(glyphs);
  delete[] features;
  hb_buffer_destroy(buffer);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return 0;
}