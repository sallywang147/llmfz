#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    sf_command(nullptr, SFC_SET_LIB_VERSION, nullptr, SF_TRUE);
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // Create a new SF_INFO struct and initialize it to zeros
  SF_INFO sfinfo = {};

  // Consume some data from the stream to set the format, channels and sections
  sfinfo.format = stream.ConsumeIntegral<int>();
  sfinfo.channels = stream.ConsumeIntegral<int>();
  sfinfo.sections = stream.ConsumeIntegral<int>();
  
  // Create a new private tag
  struct sf_private_tag *psf = (struct sf_private_tag *) malloc(sizeof(struct sf_private_tag));
  if (psf == nullptr) {
    return 0;
  }
  
  // Initialize the private tag
  psf->sf = sfinfo;
  
  // Consume some data from the stream to set normalize
  int normalize = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  double result = psf_calc_signal_max(psf, normalize);

  // Free the allocated memory
  free(psf);

  return 0;
}