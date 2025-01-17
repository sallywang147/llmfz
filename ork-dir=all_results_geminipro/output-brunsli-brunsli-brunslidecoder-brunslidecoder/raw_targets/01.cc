#include <brunsli/decode.h>
#include <brunsli/decode_jpeg.h>
#include <brunsli/status.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  brunsli::BrunsliDecoder *decoder = new brunsli::BrunsliDecoder();
  decoder->BrunsliDecoder(decoder);
  const size_t kMaxDecodedPixels = 1024 * 1024;
  brunsli::JPEGData jpeg_data;
  jpeg_data.data = stream.ConsumeRemainingBytes();
  jpeg_data.size = stream.remaining_bytes();
  brunsli::BrunsliStatus status = decoder->DecodeJPEG(
      jpeg_data, kMaxDecodedPixels, nullptr, nullptr, nullptr);
  delete decoder;
  return 0;
}