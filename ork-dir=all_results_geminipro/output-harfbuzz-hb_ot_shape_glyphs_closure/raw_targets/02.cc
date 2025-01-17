#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "hb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_font_t* font = hb_font_create();
  hb_buffer_t* buffer = hb_buffer_create();
  hb_set_t* glyphs = hb_set_create();

  // Generate random text.
  const size_t text_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char32_t> text;
  for (size_t i = 0; i < text_size; i++) {
    text.push_back(stream.ConsumeIntegralInRange<char32_t>(0, 0x10FFFF));
  }
  hb_buffer_add_utf32(buffer, text.data(), text.size(), 0, text.size());

  // Generate random features.
  const size_t num_features = stream.ConsumeIntegralInRange<size_t>(0, 10);
  std::vector<hb_feature_t> features;
  for (size_t i = 0; i < num_features; i++) {
    hb_feature_t feature;
    feature.tag = stream.ConsumeIntegralInRange<uint32_t>(0, 0xFFFFFFFF);
    feature.value = stream.ConsumeIntegralInRange<int32_t>(-1, 1);
    feature.start = stream.ConsumeIntegralInRange<unsigned int>(0, text_size);
    feature.end = stream.ConsumeIntegralInRange<unsigned int>(feature.start, text_size);
    features.push_back(feature);
  }

  // Generate random glyphs.
  const size_t num_glyphs = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  for (size_t i = 0; i < num_glyphs; i++) {
    hb_set_add(glyphs, stream.ConsumeIntegralInRange<uint32_t>(0, 0xFFFFFFFF));
  }

  // Call the function to be fuzzed.
  hb_ot_shape_glyphs_closure(font, buffer, features.data(), features.size(), glyphs);

  // Clean up.
  hb_font_destroy(font);
  hb_buffer_destroy(buffer);
  hb_set_destroy(glyphs);

  return 0;
}