#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Initialize the struct sf_private_tag object
  struct sf_private_tag psf;

  // Consume data to fill the struct
  size_t consumed = provider.ConsumeData(&psf, sizeof(psf));
  if (consumed != sizeof(psf)) {
    return 0;
  }

  // Consume remaining data for the peaks array
  std::vector<double> peaks = provider.ConsumeRemainingBytes<double>();
  if (peaks.empty()) {
    return 0;
  }

  // Consume a bool for the normalize parameter
  int normalize = provider.ConsumeBool();

  // Call the target function
  psf_calc_max_all_channels(&psf, peaks.data(), normalize);

  return 0;
}