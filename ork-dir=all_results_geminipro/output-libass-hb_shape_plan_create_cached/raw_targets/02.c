#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <hb.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  hb_face_t* face = hb_face_create_for_data(data, size);
  if (face == nullptr) {
    return 0;
  }

  hb_segment_properties_t props = {HB_DIRECTION_LTR, HB_SCRIPT_LATIN, HB_LANGUAGE_MODEL_DEFAULT};

  const int num_user_features = stream.ConsumeIntegral<int>();
  std::vector<ASS_Rect> user_features(num_user_features);
  for (int i = 0; i < num_user_features; i++) {
    user_features[i].x = stream.ConsumeIntegral<int>();
    user_features[i].y = stream.ConsumeIntegral<int>();
    user_features[i].width = stream.ConsumeIntegral<int>();
    user_features[i].height = stream.ConsumeIntegral<int>();
  }

  const int num_shapers = stream.ConsumeIntegral<int>();
  std::vector<std::string> shaper_list(num_shapers);
  for (int i = 0; i < num_shapers; i++) {
    shaper_list[i] = stream.ConsumeRemainingBytesAsString();
  }
  char** shaper_list_ptr = new char*[num_shapers];
  for (int i = 0; i < num_shapers; i++) {
    shaper_list_ptr[i] = const_cast<char*>(shaper_list[i].c_str());
  }

  hb_shape_plan_t* plan = hb_shape_plan_create_cached(face, &props, user_features.data(), num_user_features, shaper_list_ptr);
  hb_shape_plan_destroy(plan);
  hb_face_destroy(face);
  delete[] shaper_list_ptr;
  return 0;
}