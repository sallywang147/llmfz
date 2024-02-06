#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "hb.h"
#include "hb-ot.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string font_data = stream.ConsumeRemainingBytesAsString();
  hb_blob_t* font_blob = hb_blob_create((const char*)font_data.c_str(),
                                          font_data.size(),
                                          HB_MEMORY_MODE_READONLY,
                                          nullptr,
                                          nullptr);
  hb_face_t* face = hb_face_create(font_blob, 0);
  hb_blob_destroy(font_blob);

  hb_set_t* lookups = hb_set_create();
  hb_set_t* glyphs = hb_set_create();
  hb_ot_layout_lookups_substitute_closure(face, lookups, glyphs);

  hb_set_destroy(lookups);
  hb_set_destroy(glyphs);
  hb_face_destroy(face);
  return 0;
}