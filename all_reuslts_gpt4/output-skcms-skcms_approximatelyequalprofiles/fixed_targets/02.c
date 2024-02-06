#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need two skcms_ICCProfile objects for the function, so we divide the input data into two parts.
  size_t half_size = size / 2;

  skcms_ICCProfile profileA, profileB;
  if (!skcms_Parse(stream.ConsumeBytes<uint8_t>(half_size).data(), half_size, &profileA)) {
    return 0;
  }

  if (!skcms_Parse(stream.ConsumeRemainingBytes<uint8_t>().data(), size - half_size, &profileB)) {
    return 0;
  }

  skcms_ApproximatelyEqualProfiles(&profileA, &profileB);

  return 0;
}