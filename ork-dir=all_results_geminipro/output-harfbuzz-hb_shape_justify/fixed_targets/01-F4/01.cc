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
  hb_font_t* font = hb_font_create();
  hb_buffer_t* buffer = hb_buffer_create();
  std::vector<hb_glyph_extents_t> features;
  std::vector<char*> shaper_list;
  float min_target_advance = stream.ConsumeFloatingPoint<float>();
  float max_target_advance = stream.ConsumeFloatingPoint<float>();
  float advance;
  int var_tag;
  float var_value;

  const std::string text = stream.ConsumeRemainingBytesAsString();
  hb_buffer_add_utf8(buffer, text.c_str(), text.size(), 0, text.size());

  hb_shape_justify(font, buffer, features.data(), features.size(),
                  shaper_list.data(), shaper_list.size(), min_target_advance,
                  max_target_advance, &advance, &var_tag, &var_value);

  hb_font_destroy(font);
  hb_buffer_destroy(buffer);
  return 0;
}