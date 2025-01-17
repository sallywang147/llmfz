#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <memory>

#include "proj/crs.h"
#include "dropbox/oxygen/nn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the CRS object
  osgeo::proj::crs::CRS crs;

  // Initialize the dropbox::oxygen::nn object
  dropbox::oxygen::nn nn_obj;

  // Initialize the shared_ptr
  std::shared_ptr<osgeo::proj::crs::CRS> shared_ptr_obj;

  // Get an integer from the stream
  int int_arg = stream.ConsumeIntegral<int>();

  // Call the function
  crs.createBoundCRSToWGS84IfPossible(&nn_obj, &crs, &shared_ptr_obj, int_arg);

  return 0;
}