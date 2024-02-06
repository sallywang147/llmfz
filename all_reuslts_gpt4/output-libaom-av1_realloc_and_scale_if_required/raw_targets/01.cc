#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "aom/aom_image.h"
#include "aom/aom_integer.h"
#include "aom_scale/yv12config.h"
#include "av1/common/av1_common_int.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  AV1Common common = {};
  common.seq_params.use_highbitdepth = stream.ConsumeBool();

  yv12_buffer_config buf1 = {};
  yv12_buffer_config buf2 = {};

  char enable_auto_ar = stream.ConsumeIntegral<char>();
  int num_planes = stream.ConsumeIntegralInRange<int>(1, MAX_MB_PLANE);
  bool is_scaling_required = stream.ConsumeBool();
  bool is_resampling_required = stream.ConsumeBool();
  int width = stream.ConsumeIntegral<int>();
  int height = stream.ConsumeIntegral<int>();

  av1_realloc_and_scale_if_required(&common, &buf1, &buf2, enable_auto_ar, num_planes, is_scaling_required, is_resampling_required, width, height);

  return 0;
}