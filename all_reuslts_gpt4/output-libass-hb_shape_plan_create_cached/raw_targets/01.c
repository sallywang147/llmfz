#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "ass.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create a hb_face_t object
  hb_blob_t *blob = hb_blob_create(reinterpret_cast<const char*>(data), size, HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_blob_destroy(blob);

  // Create a hb_segment_properties_t object
  hb_segment_properties_t props;
  props.direction = static_cast<hb_direction_t>(stream.ConsumeIntegralInRange<int>(HB_DIRECTION_INVALID, HB_DIRECTION_TTB));
  props.script = stream.ConsumeIntegral<hb_script_t>();
  props.language = hb_language_from_string(stream.ConsumeRandomLengthString().c_str(), -1);

  // Create an ASS_Rect object
  ASS_Rect user_features;
  user_features.x = stream.ConsumeIntegral<int>();
  user_features.y = stream.ConsumeIntegral<int>();
  user_features.w = stream.ConsumeIntegral<int>();
  user_features.h = stream.ConsumeIntegral<int>();

  // Create a shaper_list
  std::vector<std::string> shaper_list_strs;
  while (stream.remaining_bytes() > 0) {
    shaper_list_strs.push_back(stream.ConsumeRandomLengthString());
  }
  std::vector<char*> shaper_list;
  for (auto& str : shaper_list_strs) {
    shaper_list.push_back(const_cast<char*>(str.c_str()));
  }
  shaper_list.push_back(nullptr);  // null-terminated list

  // Call the target function
  hb_shape_plan_t* shape_plan = hb_shape_plan_create_cached(face, &props, &user_features, shaper_list_strs.size(), shaper_list.data());

  // Cleanup
  hb_face_destroy(face);
  if (shape_plan != nullptr) {
    hb_shape_plan_destroy(shape_plan);
  }

  return 0;
}