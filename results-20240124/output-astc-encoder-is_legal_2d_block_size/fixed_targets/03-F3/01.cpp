#include <fuzzer/FuzzedDataProvider.h>
#include <astc_codec/astc_codec.h>

extern "C" {
#include <astc_codec/astc_codec_internals.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int xdim = stream.ConsumeIntegralInRange<int>(0, 100);
  int ydim = stream.ConsumeIntegralInRange<int>(0, 100);
  is_legal_2d_block_size(xdim, ydim);
  return 0;
}