#include "src/exif.h"
#include "fuzzing/datasource/datasource.hpp"
#include "shared.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzzing::datasource::Datasource ds(data, size);

  try {
    std::exception *exception = nullptr;
    const int orientation = ds.Get<int>();
    int *result = nullptr;

    const bool ok = piex::GetExifOrientation(exception, orientation, result);

    (void)ok;
  } catch (...) {
  }

  return 0;
}