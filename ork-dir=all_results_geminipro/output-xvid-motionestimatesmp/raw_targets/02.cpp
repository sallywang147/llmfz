#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

struct SMPData {
  int32_t width;
  int32_t height;
  int32_t stride;
  uint8_t *data;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int32_t width = provider.ConsumeIntegral<int32_t>();
  int32_t height = provider.ConsumeIntegral<int32_t>();
  int32_t stride = provider.ConsumeIntegral<int32_t>();
  size_t data_size = width * height * stride;
  uint8_t *data_ptr = provider.ConsumeBytes<uint8_t>(data_size);

  SMPData h;
  h.width = width;
  h.height = height;
  h.stride = stride;
  h.data = data_ptr;

  MotionEstimateSMP(&h);

  return 0;
}