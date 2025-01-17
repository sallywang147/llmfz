#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "hb.h"

extern "C" {
#include "harfbuzz/hb-ot.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_face_t* face = hb_face_create("Roboto", nullptr);
  hb_segment_properties_t* props = hb_segment_properties_create();

  hb_buffer_t* buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, (const char*)stream.ConsumeRemainingBytes(), stream.RemainingBytes(), 0, -1);

  hb_shape_plan_t* plan = hb_shape_plan_create(face, props, buffer, 0, nullptr);
  hb_face_destroy(face);
  hb_segment_properties_destroy(props);
  hb_buffer_destroy(buffer);

  hb_shape_plan_destroy(plan);
  return 0;
}