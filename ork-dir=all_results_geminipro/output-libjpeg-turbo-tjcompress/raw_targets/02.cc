#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <turbojpeg.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tjhandle handle = NULL;
  unsigned char *jpegBuf = NULL;
  unsigned long jpegSize = 0;
  int width = 0, height = 0, pixelSize = 0, jpegSubsamp = 0, jpegQual = 0, flags = 0;
  int i;

#if defined(__has_feature) && __has_feature(memory_sanitizer)
  char env[18] = "JSIMD_FORCENONE=1";

  /* The libjpeg-turbo SIMD extensions produce false positives with
     MemorySanitizer. */
  putenv(env);
#endif

  if ((handle = tjInitCompress()) == NULL)
    goto bailout;

  FuzzedDataProvider stream(data, size);

  width = stream.ConsumeIntegralInRange(1, 1024);
  height = stream.ConsumeIntegralInRange(1, 1024);
  pixelSize = stream.ConsumeIntegralInRange(1, 4);
  jpegSubsamp = stream.ConsumeIntegralInRange(0, 3);
  jpegQual = stream.ConsumeIntegralInRange(0, 100);
  flags = stream.ConsumeIntegralInRange(0, 1024);

  jpegBuf = (unsigned char *)malloc(tjBufSize(width, height, jpegSubsamp));
  if (!jpegBuf)
    goto bailout;

  if (tjCompress(handle, (unsigned char *)data, width, 0, height, pixelSize, jpegBuf, &jpegSize, jpegSubsamp, jpegQual, flags) == 0) {
    /* Touch all of the output bytes in order to catch uninitialized reads
       when using MemorySanitizer. */
    for (i = 0; i < jpegSize; i++)
      jpegBuf[i] += 1;
  }

  free(jpegBuf);
  jpegBuf = NULL;

bailout:
  if (handle)
    tjDestroy(handle);
  return 0;
}