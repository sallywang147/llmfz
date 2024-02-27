 #include <assert.h>
#include <stdlib.h>

#include <hb-ot.h>

#include "hb-fuzzer.hh"

static void
test_subset_preprocess (hb_face_t *face)
{
  hb_face_t *subset = hb_subset_preprocess (face);
  if (subset)
    hb_face_destroy (subset);
}

extern "C" int LLVMFuzzerTestOneInput (const uint8_t *data, size_t size)
{
  alloc_state = _fuzzing_alloc_state (data, size);

  hb_blob_t *blob = hb_blob_create ((const char *) data, size,
				    HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create (blob, 0);

  test_subset_preprocess (face);

  hb_face_destroy (face);
  hb_blob_destroy (blob);
  return 0;
}