#include <fuzzer/FuzzedDataProvider.h>
#include <turbojpeg.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Decompressing a JPEG image requires a valid JPEG buffer, so we consume the
  // first half of the data for that. The rest will be used for other parameters.
  size_t jpegSize = stream.remaining_bytes() / 2;
  std::string jpegBuf = stream.ConsumeBytesAsString(jpegSize);

  // Initialize a TurboJPEG decompressor handle
  tjhandle handle = tjInitDecompress();
  if (!handle) {
    return 0;
  }

  // Get the dimensions of the JPEG image
  int width, height, subsamp, colorspace;
  if (tjDecompressHeader3(handle, reinterpret_cast<unsigned char*>(jpegBuf.data()), jpegSize, &width, &height, &subsamp, &colorspace) != 0) {
    tjDestroy(handle);
    return 0;
  }

  // We'll decompress to a buffer with the same size as the JPEG buffer
  std::vector<char> dstBuf(jpegSize);

  // Consume the remaining parameters from the stream
  int pitch = stream.ConsumeIntegral<int>();
  int pixelSize = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  tjDecompress(handle, jpegBuf.data(), jpegSize, dstBuf.data(), width, pitch, height, pixelSize, flags);

  // Clean up
  tjDestroy(handle);

  return 0;
}