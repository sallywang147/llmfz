#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hb.h"
#include "hb-ft.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    hb_blob_t *blob = hb_blob_create(reinterpret_cast<const char*>(data), size, HB_MEMORY_MODE_READONLY, nullptr, nullptr);
    hb_face_t *face = hb_face_create(blob, 0);
    hb_font_t *font = hb_font_create(face);
    hb_buffer_t *buffer = hb_buffer_create();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  hb_glyph_extents_t features;
  features.x_bearing = provider.ConsumeFloatingPoint<int>();
  features.y_bearing = provider.ConsumeFloatingPoint<int>();
  features.width = provider.ConsumeFloatingPoint<int>();
  features.height = provider.ConsumeFloatingPoint<int>();

  int num_features = provider.ConsumeIntegral<int>();

  char **shaper_list = nullptr;
  if (provider.remaining_bytes() > 0) {
    std::string shaper_string = provider.ConsumeRemainingBytesAsString();
    shaper_list = new char*[1];
    shaper_list[0] = const_cast<char*>(shaper_string.c_str());
  }

  float min_target_advance = provider.ConsumeFloatingPoint<float>();
  float max_target_advance = provider.ConsumeFloatingPoint<float>();
  float advance = 0.0f;
  int var_tag = provider.ConsumeIntegral<int>();
  float var_value = 0.0f;

  hb_shape_justify(font, buffer, &features, num_features, shaper_list, min_target_advance, max_target_advance, &advance, &var_tag, &var_value);

  if (shaper_list != nullptr) {
    delete[] shaper_list;
  }

  return 0;
}