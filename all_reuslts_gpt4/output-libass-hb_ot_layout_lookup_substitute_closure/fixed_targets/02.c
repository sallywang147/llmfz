#include <fuzzer/FuzzedDataProvider.h>
#include <hb.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a face object from the input data
  hb_blob_t *blob = hb_blob_create(reinterpret_cast<const char*>(data), size, HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_blob_destroy(blob);

  // Consume data to create a lookup_index
  int lookup_index = stream.ConsumeIntegral<int>();

  // Create a set to hold glyphs
  hb_set_t *glyphs = hb_set_create();

  // Call the function to be fuzzed
  hb_ot_layout_lookup_substitute_closure(face, lookup_index, glyphs);

  // Cleanup
  hb_set_destroy(glyphs);
  hb_face_destroy(face);

  return 0;
}