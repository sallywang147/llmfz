#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

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

  // Consume data to generate parameters for INT123_open_fixed_post
  int channels = stream.ConsumeIntegral<int>();
  int encoding = stream.ConsumeIntegral<int>();

  INT123_open_fixed_post(handle, channels, encoding);

  mpg123_delete(handle);
  return 0;
}