#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "hb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  hb_buffer_t* buffer = hb_buffer_create();
  hb_shape(hb_font_get_empty(), buffer, nullptr, 0);
  hb_shape_justify_t justify;
  justify.width = stream.ConsumeIntegral<double>();
  justify.natural_width = stream.ConsumeIntegral<double>();
  justify.last_line_only = stream.ConsumeBool();
  justify.line_spacing = stream.ConsumeIntegral<double>();
  justify.gap = stream.ConsumeIntegral<double>();
  justify.cluster_level = stream.ConsumeBool();
  hb_shape_justify_append(buffer, &justify);
  hb_buffer_destroy(buffer);
  return 0;
}