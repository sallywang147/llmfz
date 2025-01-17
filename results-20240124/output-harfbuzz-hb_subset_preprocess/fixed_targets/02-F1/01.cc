#include <hb.h>
#include <stddef.h>
#include <cstdint>
#include <vector>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <hb-ot.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t num_glyphs = stream.ConsumeIntegralInRange<size_t>(1, 100);
  std::vector<hb_codepoint_t> glyphs;
  for (size_t i = 0; i < num_glyphs; ++i) {
    glyphs.push_back(stream.ConsumeIntegral<hb_codepoint_t>());
  }
  const hb_face_t* face = hb_face_create(data, size);
  hb_face_t* subset_face = hb_subset_preprocess(face, glyphs.data(), glyphs.size());
  if (subset_face) {
    hb_face_destroy(subset_face);
  }
  hb_face_destroy(face);
  return 0;
}