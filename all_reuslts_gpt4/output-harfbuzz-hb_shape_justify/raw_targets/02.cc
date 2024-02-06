#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <vector>

#include "hb.h"
#include "hb-ft.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize HarfBuzz library.
  hb_blob_t *blob = hb_blob_create((const char *)data, size, HB_MEMORY_MODE_READONLY, NULL, NULL);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  // Initialize buffer.
  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);
  hb_buffer_set_script(buffer, HB_SCRIPT_LATIN);
  hb_buffer_set_language(buffer, hb_language_from_string("en", -1));

  // Consume data for parameters.
  float min_target_advance = stream.ConsumeFloatingPoint<float>();
  float max_target_advance = stream.ConsumeFloatingPoint<float>();
  float advance = stream.ConsumeFloatingPoint<float>();
  int var_tag = stream.ConsumeIntegral<int>();
  float var_value = stream.ConsumeFloatingPoint<float>();

  // Create features array.
  int num_features = stream.ConsumeIntegralInRange<int>(0, 10);
  std::vector<hb_glyph_extents_t> features(num_features);

  // Create shaper list.
  int num_shapers = stream.ConsumeIntegralInRange<int>(0, 10);
  std::vector<std::string> shapers(num_shapers);
  std::vector<char *> shaper_list(num_shapers);
  for (int i = 0; i < num_shapers; ++i) {
    shapers[i] = stream.ConsumeRandomLengthString();
    shaper_list[i] = const_cast<char *>(shapers[i].c_str());
  }

  // Call the target function.
  hb_shape_justify(font, buffer, features.data(), num_features, shaper_list.data(), min_target_advance, max_target_advance, &advance, &var_tag, &var_value);

  // Clean up.
  hb_buffer_destroy(buffer);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return 0;
}