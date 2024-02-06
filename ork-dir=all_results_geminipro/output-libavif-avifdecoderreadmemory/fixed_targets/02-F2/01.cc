#include <vector>

#include "avif/avif.h"
#include "avif/avif_cxx.h"

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

  if (avifDecoderParse(decoder.get()) != AVIF_RESULT_OK)
    return 0;
  while (avifDecoderNextImage(decoder.get()) == AVIF_RESULT_OK) {
  }

  // Loop once.
  if (avifDecoderReset(decoder.get()) != AVIF_RESULT_OK)
    return 0;
  while (avifDecoderNextImage(decoder.get()) == AVIF_RESULT_OK) {
    avifImage *const image = avifDecoderGetImage(decoder.get());
    if (image == nullptr)
      return 0;
    // Fuzz avifDecoderReadMemory.
    const size_t image_size = avifImageSizeBytes(image);
    std::vector<uint8_t> image_data(image_size);
    if (avifDecoderReadMemory(decoder.get(), image, reinterpret_cast<char *>(image_data.data()),
                             image_size) != AVIF_RESULT_OK) {
      return 0;
    }
    avifImageDestroy(image);
  }

  return 0; // Non-zero return values are reserved for future use.
}
```

The issue is that the `avifImageDestroy` function is not called to free the memory allocated for the `avifImage` object. This can lead to memory leaks and crashes.

To fix this issue, we need to call `avifImageDestroy` after we are done with the `avifImage` object. We can do this by adding the following line after the line where we call `avifDecoderReadMemory`:

```c++
avifImageDestroy(image);
```

This will ensure that the memory allocated for the `avifImage` object is freed when we are done with it.