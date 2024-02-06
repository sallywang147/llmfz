#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <hb.h>
#include <hb-subset.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a blob from the input data
  hb_blob_t *blob = hb_blob_create(reinterpret_cast<const char*>(data), size, HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  if (hb_blob_get_length(blob) == 0) {
    hb_blob_destroy(blob);
    return 0;
  }

  // Create a face from the blob
  hb_face_t *face = hb_face_create(blob, 0);
  if (face == nullptr) {
    hb_blob_destroy(blob);
    return 0;
  }

  // Call the target function
  hb_face_t *subset_face = hb_subset_preprocess(face);

  // Clean up
  hb_face_destroy(subset_face);
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return 0;
}