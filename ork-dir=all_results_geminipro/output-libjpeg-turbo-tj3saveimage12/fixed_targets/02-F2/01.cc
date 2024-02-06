#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <turbojpeg.h>

extern "C" {
#include <jpeglib.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tjhandle handle = NULL;
  char *filename = "output.bmp";
  short *buffer = NULL;
  int width = 0, height = 0, pixelFormat = TJPF_GRAY;
  int pitch = 0;

  if ((handle = tjInitTransform()) == NULL)
    goto bailout;

  /* We ignore the return value of tjDecompressHeader3(), because some JPEG
     images may have unusual subsampling configurations that the TurboJPEG API
     cannot identify but can still transform. */
  tjDecompressHeader3(handle, data, size, &width, &height, NULL, &pixelFormat);

  /* Ignore 0-pixel images and images larger than 1 Megapixel.  Casting width
     to (uint64_t) prevents integer overflow if width * height > INT_MAX. */
  if (width < 1 || height < 1 || (uint64_t)width * height > 1048576)
    goto bailout;

  if (pixelFormat < 0 || pixelFormat >= TJ_NUMPF)
    pixelFormat = TJPF_GRAY;

  buffer = (short *)malloc(width * height * tjPixelSize[pixelFormat]);
  if (!buffer)
    goto bailout;

  pitch = width * tjPixelSize[pixelFormat];

  if (tj3SaveImage12(handle, filename, buffer, width, pitch, height, pixelFormat) == 0) {
    /* Touch all of the output pixels in order to catch uninitialized reads
       when using MemorySanitizer. */
    int sum = 0;

    for (int i = 0; i < width * height * tjPixelSize[pixelFormat]; i++)
      sum += buffer[i];

    /* Prevent the code above from being optimized out.  This test should
       never be true, but the compiler doesn't know that. */
    if (sum > 255 * width * height * tjPixelSize[pixelFormat])
      goto bailout;
  }

bailout:
  free(buffer);
  if (handle)
    tjDestroy(handle);
  return 0;
}