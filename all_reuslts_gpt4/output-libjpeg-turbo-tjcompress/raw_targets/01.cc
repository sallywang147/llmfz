#include <fuzzer/FuzzedDataProvider.h>
#include <turbojpeg.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize TurboJPEG
  tjhandle handle = tjInitCompress();
  if (!handle) {
    return 0;
  }

  // Consume data from the fuzzer input
  int width = stream.ConsumeIntegralInRange(1, 1000);
  int height = stream.ConsumeIntegralInRange(1, 1000);
  int pixelSize = stream.ConsumeIntegralInRange(1, 4);
  int pitch = width * pixelSize;
  std::vector<char> srcBuf = stream.ConsumeBytes<char>(width * height * pixelSize);
  std::vector<char> jpegBuf(width * height * pixelSize);  // Maximum possible size
  size_t jpegSize = jpegBuf.size();
  int jpegSubsamp = stream.ConsumeIntegralInRange(0, 4);  // TJ_444, TJ_422, TJ_420, TJ_GRAYSCALE, TJ_411
  int jpegQual = stream.ConsumeIntegralInRange(1, 100);
  int flags = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  tjCompress(handle, srcBuf.data(), width, pitch, height, pixelSize, jpegBuf.data(), &jpegSize, jpegSubsamp, jpegQual, flags);

  // Clean up
  tjDestroy(handle);
  
  return 0;
}