#include <fuzzer/FuzzedDataProvider.h>
#include <hb.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_blob_t *blob = hb_blob_create((const char*)data, size, HB_MEMORY_MODE_READONLY, NULL, NULL);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  hb_segment_properties_t props;
  props.direction = stream.ConsumeEnum<hb_direction_t>();
  props.script = stream.ConsumeEnum<hb_script_t>();
  props.language = hb_language_from_string(stream.ConsumeRandomLengthString().c_str(), -1);

  struct ASS_Rect {
    int x;
    int y;
    int width;
    int height;
  } user_features;

  user_features.x = stream.ConsumeIntegral<int>();
  user_features.y = stream.ConsumeIntegral<int>();
  user_features.width = stream.ConsumeIntegral<int>();
  user_features.height = stream.ConsumeIntegral<int>();

  int num_user_features = stream.ConsumeIntegralInRange<int>(0, 10);
  char **shaper_list = new char*[num_user_features];
  for (int i = 0; i < num_user_features; ++i) {
    shaper_list[i] = strdup(stream.ConsumeRandomLengthString().c_str());
  }

  hb_shape_plan_t *shape_plan = hb_shape_plan_create(face, &props, (hb_feature_t*)&user_features, num_user_features, shaper_list);

  for (int i = 0; i < num_user_features; ++i) {
    free(shaper_list[i]);
  }
  delete[] shaper_list;

  hb_shape_plan_destroy(shape_plan);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return 0;
}