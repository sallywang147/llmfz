#include <fuzzer/FuzzedDataProvider.h>
#include <webp/encode.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // The input image is represented as a flat array of RGB samples.
  // We'll consume up to half of the input data for the image.
  size_t image_size = stream.remaining_bytes() / 2;
  std::string image_data = stream.ConsumeBytesAsString(image_size);

  // The width and height of the image cannot be zero.
  // We'll consume two integers for width and height, ensuring they are at least 1.
  int width = stream.ConsumeIntegralInRange<int>(1, 1000);
  int height = stream.ConsumeIntegralInRange<int>(1, 1000);

  // The stride (number of bytes per scan line) must be at least 3*width.
  // We'll consume an integer for the stride, ensuring it is at least 3*width.
  int stride = stream.ConsumeIntegralInRange<int>(3 * width, 3000);

  // The output is a pointer to the encoded data. We'll initialize it to null.
  uint8_t* output = nullptr;

  // Call the function to fuzz
  WebPEncodeLosslessRGB(image_data.data(), width, height, stride, (char**)&output);

  // Free the output data if it was allocated
  if (output != nullptr) {
    free(output);
  }

  return 0;
}