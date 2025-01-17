#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "hb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_face_t* face = hb_face_create("Roboto", nullptr);
  hb_segment_properties_t* props = hb_segment_properties_create();
  hb_shape_plan_t* plan = hb_shape_plan_create(face, props, nullptr, 0, nullptr);
  hb_face_destroy(face);
  hb_segment_properties_destroy(props);

  stream.ConsumeRemainingBytes();

  hb_shape_plan_destroy(plan);
  return 0;
}