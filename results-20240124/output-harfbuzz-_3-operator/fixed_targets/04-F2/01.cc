#include <hb.h>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_buffer_t* buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, stream.ConsumeRandomLengthString().c_str(), -1, 0, -1);

  hb_shape_t* shape = hb_shape_create();
  hb_shape_full(shape, buffer, nullptr, 0);

  hb_shape_justify_t justify;
  hb_shape_justify_append(shape, &justify);

  double x = stream.ConsumeFloatingPoint<double>();
  double result = justify._3::operator(&(justify), x);

  hb_buffer_destroy(buffer);
  hb_shape_destroy(shape);

  return 0;
}