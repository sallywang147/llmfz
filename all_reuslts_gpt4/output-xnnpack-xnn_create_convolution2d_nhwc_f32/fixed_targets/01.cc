#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fuzzer/FuzzedDataProvider.h>

#include <xnnpack.h>

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <limits>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  xnn_status status = xnn_initialize(nullptr);
  if (status != xnn_status_success) {
    return 0;
  }

  /* Prepare a set of input arrays with fuzzer-generated data */
  alignas(16) static std::array<float, 864 + XNN_EXTRA_BYTES / sizeof(float)> w1;
  alignas(16) static std::array<float, 32 + XNN_EXTRA_BYTES / sizeof(float)> w2;
  std::generate(w1.begin(), w1.end(), [&]() mutable { return provider.ConsumeFloatingPoint<float>(); });
  std::generate(w2.begin(), w2.end(), [&]() mutable { return provider.ConsumeFloatingPoint<float>(); });

  xnn_operator_t op0 = nullptr;
  status = xnn_create_convolution2d_nhwc_f32(0 /* top padding */, 1 /* right padding */, 1 /* bottom padding */, 0 /* left padding */, 3 /* kernel height */, 3 /* kernel width */, 2 /* subsampling height */, 2 /* subsampling width */, 1 /* dilation_height */, 1 /* dilation_width */, 1 /* groups */, 3 /* input channels per group */, 32 /* output_channels_per_group */, 3 /* input pixel stride */, 32 /* output pixel stride */, w1.data(), w2.data(), provider.ConsumeFloatingPoint<float>() /* input scale */, provider.ConsumeFloatingPoint<float>() /* output scale */, 0 /* flags */, nullptr, nullptr, &op0);

  xnn_deinitialize();
  return 0;
}