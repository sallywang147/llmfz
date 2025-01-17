#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  butteraugli::ButteraugliComparator comparator;
  std::vector<double> mask1;
  std::vector<double> mask2;

  // Consume data to populate the vectors
  while (stream.remaining_bytes() > 0) {
    mask1.push_back(stream.ConsumeFloatingPoint<double>());
    mask2.push_back(stream.ConsumeFloatingPoint<double>());
  }

  comparator.Mask(&mask1, &mask2);

  return 0;
}