#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "hb.h"
#include "hb-ot.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_blob_t *blob = hb_blob_create((const char*)data, size, HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_blob_destroy(blob);

  int lookup_index = stream.ConsumeIntegral<int>();
  hb_set_t *glyphs = hb_set_create();

  hb_ot_layout_lookup_substitute_closure(face, lookup_index, glyphs);

  hb_set_destroy(glyphs);
  hb_face_destroy(face);

  return 0;
}