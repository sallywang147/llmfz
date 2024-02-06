#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "hb.h"
#include "hb-subset.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t font_size =
      stream.ConsumeIntegralInRange<size_t>(0, 100000);
  const uint8_t* font_data = stream.ConsumeBytes<uint8_t>(font_size);
  hb_blob_t* font_blob = hb_blob_create(reinterpret_cast<const char*>(font_data),
                                       font_size, HB_MEMORY_MODE_READONLY, nullptr,
                                       nullptr);
  if (font_blob == nullptr) {
    return 0;
  }
  hb_face_t* font_face = hb_face_create(font_blob, 0);
  hb_blob_destroy(font_blob);
  if (font_face == nullptr) {
    return 0;
  }
  hb_subset_preprocess(font_face);
  hb_set_t* glyphs = hb_set_create();
  hb_subset(font_face, glyphs);
  hb_set_destroy(glyphs);
  hb_face_destroy(font_face);
  return 0;
}