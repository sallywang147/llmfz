#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <turbojpeg.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <turbojpeg.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tjhandle handle = NULL;
  short *buffer = NULL;
  int width = 0, height = 0, pitch = 0, pixelFormat = 0;
  char filename[1024] = {0};
#if defined(__has_feature) && __has_feature(memory_sanitizer)
  char env[18] = "JSIMD_FORCENONE=1";

  /* The libjpeg-turbo SIMD extensions produce false positives with
     MemorySanitizer. */
  putenv(env);
#endif

  if ((handle = tjInitCompress()) == NULL)
    goto bailout;

  FuzzedDataProvider stream(data, size);

  width = stream.ConsumeIntegralInRange<int>(1, 1024);
  height = stream.ConsumeIntegralInRange<int>(1, 1024);
  pitch = stream.ConsumeIntegralInRange<int>(1, 1024);
  pixelFormat = stream.ConsumeIntegralInRange<int>(0, TJ_NUMPF);
  stream.ConsumeBytesAsString(1024, filename);

  buffer = (short *)malloc(width * height * tjPixelSize[pixelFormat]);
  if (!buffer)
    goto bailout;

  if (tj3SaveImage16(handle, filename, buffer, width, pitch, height, pixelFormat) < 0)
    goto bailout;

  free(buffer);
  buffer = NULL;

  if ((handle = tjInitDecompress()) == NULL)
    goto bailout;

  if (tjLoadImage(handle, filename, &width, &height, &pixelFormat) < 0)
    goto bailout;

  buffer = (short *)malloc(width * height * tjPixelSize[pixelFormat]);
  if (!buffer)
    goto bailout;

  if (tjDecompress2(handle, buffer, pitch, width * tjPixelSize[pixelFormat], width, height, pixelFormat, TJFLAG_LIMITSCANS) < 0)
    goto bailout;

  free(buffer);
  buffer = NULL;

bailout:
  free(buffer);
  if (handle)
    tjDestroy(handle);
  return 0;
}