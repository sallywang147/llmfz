#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "hb-ot.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  hb_face_t* face = hb_face_create_for_data(stream.ConsumeRemainingBytes(), size);
  if (face == nullptr) {
    return 0;
  }

  const int lookup_index = stream.ConsumeIntegralInRange<int>(0, 1000);
  hb_set_t* glyphs = hb_set_create();
  hb_ot_layout_lookup_substitute_closure(face, lookup_index, glyphs);
  hb_set_destroy(glyphs);
  hb_face_destroy(face);

  return 0;
}