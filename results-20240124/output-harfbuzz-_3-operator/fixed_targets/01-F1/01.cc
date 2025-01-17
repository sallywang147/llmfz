#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "hb.h"
#include "hb-ft.h"
#include "hb-ot.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* text = stream.ConsumeRandomLengthString().c_str();
  hb_font_t* font = hb_ft_font_create(nullptr, nullptr);
  hb_buffer_t* buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, text, -1, 0, -1);
  hb_shape(font, buffer, nullptr, 0);
  hb_shape_justify(font, buffer, 100);
  double x = stream.ConsumeFloatingPoint<double>();
  double y = hb_shape_justify::$_3::operator&(hb_shape_justify::$_3(), x);
  hb_buffer_destroy(buffer);
  hb_font_destroy(font);
  return 0;
}