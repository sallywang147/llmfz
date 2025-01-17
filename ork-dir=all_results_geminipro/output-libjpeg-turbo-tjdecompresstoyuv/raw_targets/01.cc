#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <turbojpeg.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tjhandle handle = NULL;
  unsigned char *dstBuf = NULL;
  int width = 0, height = 0, jpegSubsamp, jpegColorspace;
#if defined(__has_feature) && __has_feature(memory_sanitizer)
  char env[18] = "JSIMD_FORCENONE=1";

  /* The libjpeg-turbo SIMD extensions produce false positives with
     MemorySanitizer. */
  putenv(env);
#endif

  if ((handle = tjInitDecompress()) == NULL)
    goto bailout;

  /* We ignore the return value of tjDecompressHeader3(), because some JPEG
     images may have unusual subsampling configurations that the TurboJPEG API
     cannot identify but can still decompress. */
  tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace);

  /* Ignore 0-pixel images and images larger than 1 Megapixel.  Casting width
     to (uint64_t) prevents integer overflow if width * height > INT_MAX. */
  if (width < 1 || height < 1 || (uint64_t)width * height > 1048576)
    goto bailout;

  if (jpegSubsamp < 0 || jpegSubsamp >= TJ_NUMSAMP)
    jpegSubsamp = TJSAMP_444;

  dstBuf = (unsigned char *)malloc(tjBufSizeYUV(width, height, jpegSubsamp));
  if (!dstBuf)
    goto bailout;

  if (tjDecompressToYUV(handle, data, size, dstBuf, 0) == 0) {
    /* Touch all of the output pixels in order to catch uninitialized reads
       when using MemorySanitizer. */
    int sum = 0;

    for (int i = 0; i < tjBufSizeYUV(width, height, jpegSubsamp); i++)
      sum += dstBuf[i];

    /* Prevent the code above from being optimized out.  This test should
       never be true, but the compiler doesn't know that. */
    if (sum > 255 * tjBufSizeYUV(width, height, jpegSubsamp))
      goto bailout;
  }

bailout:
  free(dstBuf);
  if (handle)
    tjDestroy(handle);
  return 0;
}