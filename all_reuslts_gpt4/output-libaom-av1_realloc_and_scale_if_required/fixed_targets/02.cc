#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "aom/aom_image.h"
#include "av1/common/common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  AV1Common common;
  memset(&common, 0, sizeof(common));

  struct yv12_buffer_config src;
  memset(&src, 0, sizeof(src));

  struct yv12_buffer_config dst;
  memset(&dst, 0, sizeof(dst));

  char bit_depth = stream.ConsumeIntegralInRange<char>(8, 12);
  int use_highbitdepth = stream.ConsumeIntegralInRange<int>(0, 1);
  bool is_scaling_required = stream.ConsumeBool();
  bool is_422 = stream.ConsumeBool();
  int resize_num = stream.ConsumeIntegralInRange<int>(1, 100);
  int resize_den = stream.ConsumeIntegralInRange<int>(1, 100);

  av1_realloc_and_scale_if_required(&common, &src, &dst, bit_depth, use_highbitdepth, is_scaling_required, is_422, resize_num, resize_den);

  return 0;
}