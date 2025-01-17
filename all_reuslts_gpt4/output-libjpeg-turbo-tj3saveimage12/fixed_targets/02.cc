#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int tj3SaveImage12(char * handle, char * filename, short * buffer, int width, int pitch, int height, int pixelFormat);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string handle = stream.ConsumeRandomLengthString();
  std::string filename = stream.ConsumeRandomLengthString();

  const int width = stream.ConsumeIntegralInRange<int>(1, 1000);
  const int pitch = stream.ConsumeIntegralInRange<int>(1, 1000);
  const int height = stream.ConsumeIntegralInRange<int>(1, 1000);
  const int pixelFormat = stream.ConsumeIntegral<int>();

  std::vector<short> buffer(width * height);
  for (auto& b : buffer) {
    b = stream.ConsumeIntegral<short>();
  }

  tj3SaveImage12(const_cast<char*>(handle.c_str()), const_cast<char*>(filename.c_str()), buffer.data(), width, pitch, height, pixelFormat);

  return 0;
}