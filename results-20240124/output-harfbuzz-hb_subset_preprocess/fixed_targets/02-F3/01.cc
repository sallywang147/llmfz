#include <hb.h>
#include <hb-ot.h>
#include <hb-subset.h>

extern "C" {
#include <stddef.h>
#include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  hb_face_t *face = hb_face_create((const char *)data, size);
  if (!face) {
    return 0;
  }

  hb_subset_preprocess(face);

  hb_face_destroy(face);

  return 0;
}