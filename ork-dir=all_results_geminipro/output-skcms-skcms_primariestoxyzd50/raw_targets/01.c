#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  float rx = stream.ConsumeFloatingPoint<float>();
  float ry = stream.ConsumeFloatingPoint<float>();
  float gx = stream.ConsumeFloatingPoint<float>();
  float gy = stream.ConsumeFloatingPoint<float>();
  float bx = stream.ConsumeFloatingPoint<float>();
  float by = stream.ConsumeFloatingPoint<float>();
  float wx = stream.ConsumeFloatingPoint<float>();
  float wy = stream.ConsumeFloatingPoint<float>();
  struct skcms_Matrix3x3 toXYZD50;
  bool result = skcms_PrimariesToXYZD50(rx, ry, gx, gy, bx, by, wx, wy,
                                        &toXYZD50);
  return result ? 0 : 1;
}