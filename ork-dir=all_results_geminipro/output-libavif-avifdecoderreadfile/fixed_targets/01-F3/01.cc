#include "avif/avif.h"
#include "avif/avif_cxx.h"
#include "avif/avif_io.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  avif::DecoderPtr decoder(avifDecoderCreate());
  if (decoder == nullptr)
    return 0;
  decoder->allowProgressive = AVIF_TRUE;

  // ClusterFuzz passes -rss_limit_mb=2560 to avif_decode_fuzzer. Empirically
  // setting decoder->imageSizeLimit to this value allows avif_decode_fuzzer to
  // consume no more than 2560 MB of memory. Also limit the dimensions to avoid
  // timeouts and to speed the fuzzing up.
  constexpr uint32_t kImageSizeLimit = 8 * 1024 * 8 * 1024;
  static_assert(kImageSizeLimit <= AVIF_DEFAULT_IMAGE_SIZE_LIMIT, "");
  decoder->imageSizeLimit = kImageSizeLimit;

  avifIO *const io = avifIOCreateMemoryReader(Data, Size);
  if (io == nullptr)
    return 0;
  // Simulate Chrome's avifIO object, which is not persistent.
  io->persistent = AVIF_FALSE;
  avifDecoderSetIO(decoder.get(), io);

  avifImage *const image = avifImageCreateEmpty();
  if (image == nullptr)
    return 0;

  if (avifDecoderReadFile(decoder.get(), image, nullptr) != AVIF_RESULT_OK)
    return 0;

  avifImageDestroy(image);
  avifIOFree(io);

  return 0; // Non-zero return values are reserved for future use.
}