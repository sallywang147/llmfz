#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>
#include <vector>

#include "fuzzing/datasource/datasource.hpp"
#include "piex.h"
#include "shared.h"

extern "C" {
#include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzzing::datasource::Datasource ds(data, size);

  try {
    const auto tiffData = ds.GetData(0);

    FuzzingStreamInterface stream(tiffData);

    std::exception *exception = nullptr;
    int width = 0;
    int height = 0;
    std::vector<uint8_t> jpeg_data;

    const bool ok = piex::GetDngInformation(&stream, exception, &width, &height, &jpeg_data);

    if (ok) {
      (void)width;
      (void)height;
      (void)jpeg_data;
    }
  } catch (...) {
  }

  return 0;
}