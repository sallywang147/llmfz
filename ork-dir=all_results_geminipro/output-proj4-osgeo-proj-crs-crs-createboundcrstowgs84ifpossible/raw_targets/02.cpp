#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"
#include "proj/crs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  osgeo::proj::crs::CRS crs;
  crs.fromWKT(str);
  std::shared_ptr<osgeo::proj::crs::CRS> bound_crs;
  crs.createBoundCRSToWGS84IfPossible(nullptr, bound_crs.get(), nullptr, 0);
  return 0;
}