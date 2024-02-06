#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "turbojpeg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int width = stream.ConsumeIntegralInRange<int>(0, 4096);
  int pitch = stream.ConsumeIntegralInRange<int>(0, 4096);
  int height = stream.ConsumeIntegralInRange<int>(0, 4096);
  int pixelFormat = stream.ConsumeIntegral<int>();

  // Consume some bytes for the filename
  std::string filename = stream.ConsumeBytesAsString(20);
  
  // Consume the remaining bytes for the buffer
  std::vector<short> buffer = stream.ConsumeRemainingBytes<short>();
  
  // Call the function
  tj3SaveImage16(nullptr, const_cast<char *>(filename.c_str()), buffer.data(), width, pitch, height, pixelFormat);

  return 0;
}