#include <assert.h>
#include <stdlib.h>

#include <hb-ot.h>

#include "hb-fuzzer.hh"

extern "C" {
#include <hb.h>
#include <hb-subset.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  alloc_state = _fuzzing_alloc_state(data, size);

  hb_blob_t* blob = hb_blob_create((const char*)data, size,
                                   HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t* face = hb_face_create(blob, 0);

  hb_subset_input_t* input = hb_subset_input_create_or_fail();
  hb_set_subset_input_glyphs(input, "abc", 3);

  hb_subset_face_t* subset_face = hb_subset_or_fail(face, input);

  hb_face_destroy(face);
  hb_subset_face_destroy(subset_face);
  hb_subset_input_destroy(input);
  hb_blob_destroy(blob);

  return 0;
}