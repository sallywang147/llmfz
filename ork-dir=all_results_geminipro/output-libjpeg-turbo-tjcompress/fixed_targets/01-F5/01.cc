#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <turbojpeg.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tjhandle handle = NULL;
  unsigned char *jpegBuf = NULL;
  unsigned long jpegSize = 0;
  int width = 0, height = 0, pixelSize = 0, jpegSubsamp = 0, jpegQual = 0, flags = 0;
  FuzzedDataProvider stream(data, size);

  if ((handle = tjInitCompress()) == NULL)
    goto bailout;

  width = stream.ConsumeIntegralInRange(1, 1024);
  height = stream.ConsumeIntegralInRange(1, 1024);
  pixelSize = stream.ConsumeIntegralInRange(1, 4);
  jpegSubsamp = stream.ConsumeIntegralInRange(0, 3);
  jpegQual = stream.ConsumeIntegralInRange(1, 100);
  flags = stream.ConsumeIntegralInRange(0, 1024);

  jpegBuf = (unsigned char *)malloc(tjBufSize(width, height, jpegSubsamp));
  if (!jpegBuf)
    goto bailout;

  if (tjCompress(handle, (unsigned char *)data, width, 0, height, pixelSize, jpegBuf, &jpegSize, jpegSubsamp, jpegQual, flags) == 0) {
    int sum = 0;

    for (int i = 0; i < jpegSize; i++)
      sum += jpegBuf[i];

    if (sum > 255 * tjBufSize(width, height, jpegSubsamp))
      goto bailout;
  }

bailout:
  free(jpegBuf);
  if (handle)
    tjDestroy(handle);
  return 0;
}