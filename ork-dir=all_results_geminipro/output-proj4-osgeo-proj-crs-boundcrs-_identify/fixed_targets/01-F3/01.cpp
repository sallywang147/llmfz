#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <list>
#include <memory>
#include <string>
#include <vector>

extern "C" {
#include "proj/crs.hpp"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::list<osgeo::proj::crs::BoundCRS> bound_crs_list;
  std::vector<std::shared_ptr<osgeo::proj::crs::BoundCRS>> bound_crs_ptrs;
  for (size_t i = 0; i < stream.ConsumeIntegral<uint8_t>(); ++i) {
    bound_crs_list.emplace_back();
    bound_crs_ptrs.emplace_back(std::make_shared<osgeo::proj::crs::BoundCRS>());
  }
  osgeo::proj::crs::BoundCRS bound_crs;
  bound_crs._identify(&bound_crs_list, &bound_crs, &bound_crs_ptrs);
  return 0;
}