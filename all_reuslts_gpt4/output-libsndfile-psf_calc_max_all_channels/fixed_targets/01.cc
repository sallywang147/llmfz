#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the required parameters for the function
  struct sf_private_tag psf;
  int normalize = stream.ConsumeIntegral<int>();
  size_t peaks_size = stream.ConsumeIntegralInRange<size_t>(0, 100); // Limiting the size to avoid memory exhaustion
  std::vector<double> peaks(peaks_size);

  // Initialize the struct members
  memset(&psf, 0, sizeof(psf));

  // Consume data for the struct members
  psf.samplerate = stream.ConsumeIntegral<int>();
  psf.channels = stream.ConsumeIntegral<int>();
  psf.logindex = stream.ConsumeIntegral<int>();
  psf.bytewidth = stream.ConsumeIntegral<int>();
  psf.endianness = stream.ConsumeIntegral<int>();
  psf.float_endswap = stream.ConsumeBool();

  // Call the function to fuzz
  psf_calc_max_all_channels(&psf, peaks.data(), normalize);

  return 0;
}