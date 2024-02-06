#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tj3.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the parameters for the tj3SaveImage12 function
  int width = stream.ConsumeIntegralInRange<int>(0, 1000);
  int pitch = stream.ConsumeIntegralInRange<int>(0, 1000);
  int height = stream.ConsumeIntegralInRange<int>(0, 1000);
  int pixelFormat = stream.ConsumeIntegralInRange<int>(0, 10);

  // Define the buffer size based on the width, height and pitch
  int bufferSize = width * height * pitch;
  std::vector<short> buffer(bufferSize);

  // Consume data for the buffer
  for (int i = 0; i < bufferSize; ++i) {
    buffer[i] = stream.ConsumeIntegral<short>();
  }

  // Define the handle and filename
  std::string handle = stream.ConsumeBytesAsString(10);
  std::string filename = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  tj3SaveImage12(const_cast<char*>(handle.c_str()), const_cast<char*>(filename.c_str()), buffer.data(), width, pitch, height, pixelFormat);

  return 0;
}