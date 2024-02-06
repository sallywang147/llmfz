#include <fuzzer/FuzzedDataProvider.h>
#include <turbojpeg.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize TurboJPEG
  tjhandle handle = tjInitCompress();
  if (!handle) {
    return 0;
  }

  // Consume data for parameters
  int width = stream.ConsumeIntegralInRange<int>(1, 1000);
  int pitch = stream.ConsumeIntegralInRange<int>(0, 1000);
  int height = stream.ConsumeIntegralInRange<int>(1, 1000);
  int pixelSize = stream.ConsumeIntegralInRange<int>(1, 4);
  int jpegSubsamp = stream.ConsumeIntegralInRange<int>(TJSAMP_444, TJSAMP_GRAY);
  int jpegQual = stream.ConsumeIntegralInRange<int>(1, 100);
  int flags = stream.ConsumeIntegral<int>();

  // Prepare source buffer
  size_t srcBufSize = width * height * pixelSize;
  std::vector<char> srcBuf = stream.ConsumeBytes<char>(srcBufSize);
  if (srcBuf.size() != srcBufSize) {
    tjDestroy(handle);
    return 0;
  }

  // Prepare output buffer
  size_t jpegSize = tjBufSize(width, height, jpegSubsamp);
  std::vector<char> jpegBuf(jpegSize);

  // Call the target function
  int result = tjCompress2(handle, reinterpret_cast<unsigned char*>(srcBuf.data()), width, pitch, height, pixelSize,
                           reinterpret_cast<unsigned char*>(jpegBuf.data()), &jpegSize, jpegSubsamp, jpegQual, flags);

  // Cleanup
  tjDestroy(handle);

  return 0;
}