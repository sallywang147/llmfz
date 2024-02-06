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

  hb_blob_t *blob = hb_blob_create((const char *)data, size,
                                   HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create(blob, 0 /* first face */);
  hb_blob_destroy(blob);

  if (!face) {
    return 0;
  }

  hb_font_t *font = hb_font_create(face);

  hb_set_t *lookups = hb_set_create();
  hb_set_t *glyphs = hb_set_create();

  // Consume data to initialize the lookups and glyphs sets
  while (stream.remaining_bytes() > 0) {
    hb_codepoint_t codepoint = stream.ConsumeIntegral<hb_codepoint_t>();
    hb_set_add(lookups, codepoint);
    hb_set_add(glyphs, codepoint);
  }

  hb_ot_layout_lookups_substitute_closure(face, lookups, glyphs);

  hb_set_destroy(lookups);
  hb_set_destroy(glyphs);
  hb_font_destroy(font);
  hb_face_destroy(face);

  return 0;
}