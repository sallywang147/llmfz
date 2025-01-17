#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
void MotionEstimateSMP(struct SMPData * h);
}

struct SMPData {
  int32_t width;
  int32_t height;
  int32_t stride;
  int16_t *data;
};

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct SMPData h;
  h.width = provider.ConsumeIntegral<int32_t>();
  h.height = provider.ConsumeIntegral<int32_t>();
  h.stride = provider.ConsumeIntegral<int32_t>();
  h.data = (int16_t *)provider.ConsumeBytes<int16_t>(h.width * h.height * h.stride);

  MotionEstimateSMP(&h);

  return 0;
}
}

extern "C" {
void MotionEstimateSMP(struct SMPData * h) {
  // ...
}
}