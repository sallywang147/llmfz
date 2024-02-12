#include <hb.h>
#include <hb-ot.h>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  hb_buffer_t* buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, stream.ConsumeRandomLengthString().c_str(), -1, 0, -1);
  hb_font_t* font = hb_font_create();
  hb_shape(font, buffer, nullptr, 0);
  // Call the missing function here
  hb_shape_justify(buffer, stream.ConsumeIntegral<double>(), stream.ConsumeIntegral<double>(), stream.ConsumeIntegral<double>());
  hb_shape_plan_t* plan = hb_shape_plan_create(font, buffer, nullptr, 0);
  hb_shape_plan_execute(plan, buffer, nullptr);
  hb_shape_plan_destroy(plan);
  hb_font_destroy(font);
  hb_buffer_destroy(buffer);
  return 0;
}