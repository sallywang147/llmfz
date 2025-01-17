#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create an instance of ButteraugliComparator
  butteraugli::ButteraugliComparator comparator;

  // Create the vectors to be passed as parameters
  std::vector<double> v1, v2;

  // Fill the vectors with data from the fuzzer
  while (stream.remaining_bytes() > 0) {
    v1.push_back(stream.ConsumeFloatingPoint<double>());
    v2.push_back(stream.ConsumeFloatingPoint<double>());
  }

  // Call the function to be fuzzed
  comparator.Mask(&comparator, &v1, &v2);

  return 0;
}