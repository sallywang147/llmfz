#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "hb-subset.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Create an hb_blob_t from the input data
  hb_blob_t* blob = hb_blob_create(reinterpret_cast<const char*>(data), size,
                                   HB_MEMORY_MODE_READONLY, nullptr, nullptr);

  // Create an hb_face_t from the blob
  hb_face_t* face = hb_face_create(blob, 0);

  // Call the target function
  hb_face_t* result = hb_subset_preprocess(face);

  // Cleanup
  hb_face_destroy(result);
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return 0;
}