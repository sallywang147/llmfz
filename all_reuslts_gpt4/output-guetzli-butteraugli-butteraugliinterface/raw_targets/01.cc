#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the vectors and the Image
  std::vector<butteraugli::Image> image_vector1;
  std::vector<butteraugli::Image> image_vector2;
  butteraugli::Image image;
  double result;

  // Populate the vectors with Images
  while (stream.remaining_bytes() > 0) {
    // Consume data for the Image
    int xsize = stream.ConsumeIntegral<int>();
    int ysize = stream.ConsumeIntegral<int>();
    int num_pixels = xsize * ysize;

    // Check if there is enough data left for the Image
    if (stream.remaining_bytes() < num_pixels * 3) {
      break;
    }

    // Create the Image and populate it with data
    butteraugli::Image img(xsize, ysize);
    for (int i = 0; i < num_pixels; ++i) {
      img.PlaneRow(0, i)[0] = stream.ConsumeFloatingPoint<float>();
      img.PlaneRow(1, i)[0] = stream.ConsumeFloatingPoint<float>();
      img.PlaneRow(2, i)[0] = stream.ConsumeFloatingPoint<float>();
    }

    // Add the Image to the vectors
    image_vector1.push_back(img);
    image_vector2.push_back(img);
  }

  // Call the function to fuzz
  butteraugli::ButteraugliInterface(&image_vector1, &image_vector2, &image, &result);

  return 0;
}