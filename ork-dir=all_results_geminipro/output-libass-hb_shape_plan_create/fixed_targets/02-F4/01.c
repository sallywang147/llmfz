#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "hb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_face_t* face = hb_face_create_for_data(stream.ConsumeRemainingBytes(), size);
  if (face == nullptr) {
    return 0;
  }

  hb_segment_properties_t* props = hb_segment_properties_create();
  hb_segment_properties_set_direction(props, HB_DIRECTION_LTR);
  hb_segment_properties_set_script(props, HB_SCRIPT_LATIN);

  struct hb_shape_plan_t* plan = hb_shape_plan_create(face, props, nullptr, 0, nullptr);
  hb_shape_plan_destroy(plan);
  hb_segment_properties_destroy(props);
  hb_face_destroy(face);
  return 0;
}