#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "motion_estimate.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  SMPData smpData;
  size_t consumed = stream.ConsumeData(&smpData, sizeof(smpData));

  if (consumed != sizeof(smpData)) {
    return 0;
  }

  MotionEstimateSMP(&smpData);

  return 0;
}