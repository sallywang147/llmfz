#include <hb-shape.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <hb-shape-justify.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  hb_shape_justify::anon anon;
  double x = stream.ConsumeFloatingPoint<double>();
  double ret = anon(x);

  return 0;
}