#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <turbojpeg.h>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tjhandle handle = NULL;
  char *filename = NULL;
  short *buffer = NULL;
  int width = 0, height = 0, pitch = 0, pixelFormat = 0;
  FuzzedDataProvider stream(data, size);

  if ((handle = tjInitTransform()) == NULL)
    goto bailout;

  filename = stream.ConsumeRandomLengthString().c_str();
  width = stream.ConsumeIntegralInRange<int>(1, 1024);
  height = stream.ConsumeIntegralInRange<int>(1, 1024);
  pitch = stream.ConsumeIntegralInRange<int>(1, 1024);
  pixelFormat = stream.ConsumeIntegralInRange<int>(0, 15);
  buffer = (short *)malloc(width * height * 2);
  if (!buffer)
    goto bailout;

  tj3SaveImage16(handle, filename, buffer, width, pitch, height, pixelFormat);

  free(buffer);
  buffer = NULL;

bailout:
  if (handle)
    tjDestroy(handle);
  return 0;
}