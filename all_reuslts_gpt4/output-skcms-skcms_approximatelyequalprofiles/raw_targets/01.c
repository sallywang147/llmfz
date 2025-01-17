#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Divide the input data into two parts for two profiles
  size_t sizeA = stream.remaining_bytes() / 2;
  size_t sizeB = stream.remaining_bytes() - sizeA;

  std::vector<uint8_t> dataA = stream.ConsumeBytes<uint8_t>(sizeA);
  std::vector<uint8_t> dataB = stream.ConsumeRemainingBytes<uint8_t>();

  skcms_ICCProfile profileA, profileB;

  // Parse the profiles from the input data
  if (!skcms_Parse(dataA.data(), dataA.size(), &profileA) ||
      !skcms_Parse(dataB.data(), dataB.size(), &profileB)) {
    return 0;
  }

  // Call the target function
  skcms_ApproximatelyEqualProfiles(&profileA, &profileB);

  return 0;
}