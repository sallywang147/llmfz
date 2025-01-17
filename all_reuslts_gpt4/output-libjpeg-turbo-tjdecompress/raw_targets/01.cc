#include <fuzzer/FuzzedDataProvider.h>
#include <turbojpeg.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Decompressing a JPEG image of size 0 or 1 is not meaningful, so we return early.
  if (size < 2) {
    return 0;
  }

  tjhandle handle = tjInitDecompress();
  if (!handle) {
    return 0;
  }

  int width, height;
  if (tjDecompressHeader(handle, stream.data(), size, &width, &height) != 0) {
    tjDestroy(handle);
    return 0;
  }

  int pixelSize = stream.ConsumeIntegralInRange<int>(1, 4);
  int pitch = stream.ConsumeIntegralInRange<int>(0, width * pixelSize);
  int flags = stream.ConsumeIntegral<int>();

  std::vector<char> dstBuf(width * height * pixelSize);

  tjDecompress(handle, stream.data(), size, dstBuf.data(), width, pitch, height, pixelSize, flags);

  tjDestroy(handle);
  return 0;
}