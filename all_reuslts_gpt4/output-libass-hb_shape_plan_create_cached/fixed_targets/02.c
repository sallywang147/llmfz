#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "hb-ft.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_blob_t *blob = hb_blob_create((const char *)data, size, HB_MEMORY_MODE_READONLY, NULL, NULL);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  hb_segment_properties_t props;
  props.direction = stream.PickValueInArray({HB_DIRECTION_LTR, HB_DIRECTION_RTL, HB_DIRECTION_TTB, HB_DIRECTION_BTT});
  props.script = stream.ConsumeIntegral<hb_script_t>();
  props.language = hb_language_from_string(stream.ConsumeRandomLengthString().c_str(), -1);
  
  std::vector<char*> shaper_list;
  while (stream.remaining_bytes() > 0) {
    std::string shaper = stream.ConsumeRandomLengthString();
    char* shaper_cstr = new char[shaper.size() + 1];
    std::copy(shaper.begin(), shaper.end(), shaper_cstr);
    shaper_cstr[shaper.size()] = '\0';
    shaper_list.push_back(shaper_cstr);
  }
  shaper_list.push_back(NULL);

  hb_shape_plan_t *shape_plan = hb_shape_plan_create_cached(face, &props, NULL, 0, shaper_list.data());

  hb_shape_plan_destroy(shape_plan);
  for (char* shaper : shaper_list) {
    delete[] shaper;
  }
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return 0;
}