#include "src/tiff_parser.h"
#include "fuzzing/datasource/datasource.hpp"
#include "shared.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" {
#include <exception>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzzing::datasource::Datasource ds(data, size);

  try {
    const auto tiffData = ds.GetData(0);

    FuzzingStreamInterface stream(tiffData);
    const auto tagSet = getTagSet(ds);
    const auto max_number_ifds = ds.Get<uint16_t>();

    /* XXX To prevent stack overflow. Remove this once upstream is fixed */
    if (max_number_ifds > 100) {
      return 0;
    }

    piex::TiffParser parser(&stream, 0);
    piex::TiffContent tiff_content;
    const bool parseOk = parser.Parse(tagSet, max_number_ifds, &tiff_content);

    if (parseOk && !tiff_content.tiff_directory.empty()) {
      std::exception *exception = nullptr;
      int *int_ptr = nullptr;

      const bool ok = piex::GetExceptionAndIntPointer(exception, int_ptr);

      if (ok) {
        (void)exception;
        (void)int_ptr;
      }
    }
  } catch (...) {
  }

  return 0;
}

namespace piex {

bool GetExceptionAndIntPointer(std::exception *&exception, int *&int_ptr) {
  // Implement the function
  return false;
}

}  // namespace piex