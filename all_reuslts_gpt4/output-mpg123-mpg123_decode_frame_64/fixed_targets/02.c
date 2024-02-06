#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mpg123.h"
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    mpg123_init();
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  int error;
  mpg123_handle *handle = mpg123_new(NULL, &error);
  if (handle == NULL || mpg123_param(handle, MPG123_ADD_FLAGS, MPG123_QUIET, 0.) != MPG123_OK) {
    return 0;
  }

  size_t outmemorysize = stream.ConsumeIntegralInRange<size_t>(0, size);
  unsigned char *outmemory = (unsigned char *)malloc(outmemorysize);
  if (outmemory == NULL) {
    return 0;
  }

  size_t num = 0;
  size_t bytes = 0;
  char *audio = (char *)outmemory;
  
  if (mpg123_open_feed(handle) == MPG123_OK) {
    if (mpg123_feed(handle, data, size) == MPG123_OK) {
      mpg123_decode_frame_64(handle, &num, &audio, &bytes);
    }
  }

  mpg123_close(handle);
  mpg123_delete(handle);
  free(outmemory);
  return 0;
}