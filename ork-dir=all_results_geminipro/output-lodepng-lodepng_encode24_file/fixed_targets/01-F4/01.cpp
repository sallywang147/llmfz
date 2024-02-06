#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstring>
#include <string>

extern "C" {
#include <lodepng.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate a random filename.
  std::string filename = stream.ConsumeRandomLengthString(16);
  filename += ".png";

  // Generate a random image.
  const uint32_t width = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  const uint32_t height = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  std::vector<uint8_t> image(width * height * 3);
  stream.ConsumeBytes<uint8_t>(image.data(), image.size());

  // Call the function to be fuzzed.
  int result = lodepng_encode24_file(filename.c_str(), reinterpret_cast<unsigned char*>(image.data()), width, height);
  if (result != 0) {
    // An error occurred.
    return 0;
  }

  // The function returned successfully.
  return 0;
}