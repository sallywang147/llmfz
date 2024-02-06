#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <list>
#include <memory>

#include "proj/crs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::list<osgeo::proj::crs::BoundCRS> list;
  osgeo::proj::crs::BoundCRS boundCRS;
  std::shared_ptr<osgeo::proj::crs::BoundCRS> sharedPtr = std::make_shared<osgeo::proj::crs::BoundCRS>();

  boundCRS._identify(&list, &boundCRS, &sharedPtr);

  return 0;
}