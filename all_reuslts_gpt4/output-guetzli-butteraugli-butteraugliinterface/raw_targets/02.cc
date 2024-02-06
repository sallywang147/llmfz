#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create the first vector
  size_t vector1_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<float> vector1(vector1_size);
  for (size_t i = 0; i < vector1_size; ++i) {
    vector1[i] = stream.ConsumeFloatingPoint<float>();
  }

  // Create the second vector
  size_t vector2_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<float> vector2(vector2_size);
  for (size_t i = 0; i < vector2_size; ++i) {
    vector2[i] = stream.ConsumeFloatingPoint<float>();
  }

  // Create the image
  size_t xsize = stream.ConsumeIntegralInRange<size_t>(0, 100);
  size_t ysize = stream.ConsumeIntegralInRange<size_t>(0, 100);
  butteraugli::Image image(xsize, ysize);

  // Create the double
  double value = stream.ConsumeFloatingPoint<double>();

  // Call the function
  butteraugli::ButteraugliInterface(&vector1, &vector2, &image, &value);

  return 0;
}