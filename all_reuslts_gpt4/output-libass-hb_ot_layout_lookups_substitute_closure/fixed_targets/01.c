#include <fuzzer/FuzzedDataProvider.h>
#include <hb.h>
#include <hb-ot.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a blob using the fuzzed data. This blob will be used to create a face.
  hb_blob_t* blob = hb_blob_create(reinterpret_cast<const char*>(data), size, HB_MEMORY_MODE_READONLY, nullptr, nullptr);

  // Create a face using the blob.
  hb_face_t* face = hb_face_create(blob, 0 /* first face */);
  if (hb_face_is_immutable(face)) {
    hb_face_destroy(face);
    hb_blob_destroy(blob);
    return 0;
  }

  // Create a set for lookups.
  hb_set_t* lookups = hb_set_create();

  // Create a set for glyphs.
  hb_set_t* glyphs = hb_set_create();

  // Call the function under test.
  hb_ot_layout_lookups_substitute_closure(face, lookups, glyphs);

  // Clean up.
  hb_set_destroy(glyphs);
  hb_set_destroy(lookups);
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return 0;
}