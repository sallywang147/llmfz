#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "hb-glib.h"
#include "hb.h"
#include "hb-ot.h"

extern "C" {
#include "hb-glib.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  hb_buffer_t* buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, text.c_str(), text.length(), 0, text.length());
  hb_font_t* font = hb_font_create();
  hb_ot_shape_glyphs_closure(font, buffer, nullptr, 0, nullptr);
  hb_buffer_destroy(buffer);
  hb_font_destroy(font);
  return 0;
}