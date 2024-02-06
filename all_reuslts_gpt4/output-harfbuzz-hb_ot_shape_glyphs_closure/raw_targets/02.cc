#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "hb-ot.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  hb_blob_t *blob = hb_blob_create((const char*)stream.data(), stream.size(), HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, (const char*)stream.data(), stream.size(), 0, -1);

  hb_feature_t features[1];
  features[0].tag = HB_TAG('c', 'a', 'l', 't');
  features[0].value = 1;
  features[0].start = HB_FEATURE_GLOBAL_START;
  features[0].end = HB_FEATURE_GLOBAL_END;

  hb_set_t *glyphs = hb_set_create();

  hb_ot_shape_glyphs_closure(font, buffer, features, 1, glyphs);

  hb_set_destroy(glyphs);
  hb_buffer_destroy(buffer);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return 0;
}