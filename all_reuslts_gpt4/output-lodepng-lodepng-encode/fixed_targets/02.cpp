#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();
  int colortype = stream.ConsumeIntegral<int>();
  int bitdepth = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string filename = stream.ConsumeRandomLengthString();

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> in_bytes = stream.ConsumeRemainingBytes<uint8_t>();

  // Ensure that the input array has enough data for the given width and height
  if (w * h > in_bytes.size()) {
    return 0;
  }

  // Call the target function
  lodepng::encode(&filename, reinterpret_cast<char*>(in_bytes.data()), w, h, colortype, bitdepth);

  return 0;
}