#include <fuzzer/FuzzedDataProvider.h>

#include <list>
#include <memory>
#include <string>

#include "proj/crs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::list<osgeo::proj::crs::BoundCRS> bound_crs_list;
  osgeo::proj::crs::BoundCRS bound_crs;
  std::shared_ptr<osgeo::proj::crs::BoundCRS> bound_crs_ptr;

  bound_crs._identify(&bound_crs_list, &bound_crs, &bound_crs_ptr);

  return 0;
}