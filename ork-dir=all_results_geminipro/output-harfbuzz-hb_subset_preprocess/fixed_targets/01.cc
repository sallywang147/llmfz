#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "hb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string font_data = stream.ConsumeRemainingBytesAsString();
  hb_blob_t* font_blob = hb_blob_create(const_cast<char*>(font_data.c_str()),
                                       font_data.size(),
                                       HB_MEMORY_MODE_READONLY,
                                       nullptr,
                                       nullptr);
  if (font_blob == nullptr) {
    return 0;
  }
  hb_face_t* font_face = hb_face_create(font_blob, 0);
  if (font_face == nullptr) {
    hb_blob_destroy(font_blob);
    return 0;
  }
  hb_face_t* subset_face = hb_subset_preprocess(font_face);
  hb_face_destroy(font_face);
  if (subset_face != nullptr) {
    hb_face_destroy(subset_face);
  }
  hb_blob_destroy(font_blob);
  return 0;
}