#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "hb.h"
#include "hb-set.h"  // Include the header file `hb-set.h`

extern "C" {
#include "hb-ot.h"  // Include the header file `hb-ot.h`
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string font_data = stream.ConsumeRemainingBytesAsString();
  hb_blob_t* font_blob = hb_blob_create(font_data.c_str(), font_data.size(),
                                         HB_MEMORY_MODE_READONLY, nullptr,
                                         nullptr);
  if (font_blob == nullptr) {
    return 0;
  }
  hb_face_t* face = hb_face_create(font_blob, 0);
  hb_blob_destroy(font_blob);
  if (face == nullptr) {
    return 0;
  }

  const int lookup_index = stream.ConsumeIntegral<int>();
  hb_set_t* glyphs = hb_set_create();  // Use `hb_set_create` to create a set
  hb_ot_layout_lookup_substitute_closure(face, lookup_index, glyphs);
  hb_set_destroy(glyphs);
  hb_face_destroy(face);
  return 0;
}