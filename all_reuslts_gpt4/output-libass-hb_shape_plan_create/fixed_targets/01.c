#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "hb-ot.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    hb_blob_t *blob = hb_blob_create(reinterpret_cast<const char*>(data), size, HB_MEMORY_MODE_READONLY, nullptr, nullptr);
    hb_face_t *face = hb_face_create(blob, 0);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  
  hb_segment_properties_t props;
  props.direction = provider.ConsumeEnum<hb_direction_t>();
  props.script = provider.ConsumeEnum<hb_script_t>();
  props.language = hb_language_from_string(provider.ConsumeRandomLengthString().c_str(), -1);
  
  ASS_Rect user_features;
  user_features.x = provider.ConsumeIntegral<int>();
  user_features.y = provider.ConsumeIntegral<int>();
  user_features.w = provider.ConsumeIntegral<int>();
  user_features.h = provider.ConsumeIntegral<int>();

  int num_user_features = provider.remaining_bytes() / sizeof(ASS_Rect);
  std::vector<ASS_Rect> user_features_array = provider.ConsumeBytes<ASS_Rect>(num_user_features * sizeof(ASS_Rect));

  char *shaper_list[] = { "ot", "fallback" };

  hb_shape_plan_t *shape_plan = hb_shape_plan_create(face, &props, user_features_array.data(), num_user_features, shaper_list);

  hb_shape_plan_destroy(shape_plan);
  
  return 0;
}