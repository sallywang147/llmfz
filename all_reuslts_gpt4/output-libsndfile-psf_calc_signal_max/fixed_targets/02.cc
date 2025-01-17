#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the sf_private_tag structure
  struct sf_private_tag psf;

  // Fill the structure with data from the fuzzer
  if (size < sizeof(psf)) {
    return 0;
  }
  stream.ConsumeData(&psf, sizeof(psf));

  // Get the normalize value from the fuzzer
  int normalize = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  double result = psf_calc_signal_max(&psf, normalize);

  return 0;
}