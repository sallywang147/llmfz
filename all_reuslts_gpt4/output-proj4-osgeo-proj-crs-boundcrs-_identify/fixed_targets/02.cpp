#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <list>
#include <memory>

#include "proj/crs.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize BoundCRS object
  osgeo::proj::crs::BoundCRS boundCRS;

  // Initialize a list
  std::list<osgeo::proj::crs::BoundCRS> boundCRSList;

  // Initialize a shared_ptr
  std::shared_ptr<osgeo::proj::crs::BoundCRS> boundCRSptr(new osgeo::proj::crs::BoundCRS);

  // Call the function to fuzz
  boundCRS._identify(&boundCRSList, &boundCRS, &boundCRSptr);

  return 0;
}