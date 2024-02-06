#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "proj/crs.hpp"
#include "proj/crs_wkt.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string wkt = stream.ConsumeRemainingBytesAsString();
  osgeo::proj::crs::CRS source_crs;
  if (!osgeo::proj::crs::wkt::from_wkt(wkt, source_crs)) {
    return 0;
  }

  std::shared_ptr<osgeo::proj::crs::CRS> target_crs;
  source_crs.createBoundCRSToWGS84IfPossible(nullptr, target_crs.get(), nullptr, 0);
  return 0;
}