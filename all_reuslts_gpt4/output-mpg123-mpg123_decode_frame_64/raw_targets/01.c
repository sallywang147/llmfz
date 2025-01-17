#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "mpg123.h"
#include "fuzzer/FuzzedDataProvider.h"

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

  size_t num = stream.ConsumeIntegral<size_t>();
  size_t bytes = stream.ConsumeIntegral<size_t>();

  char *audio = (char *)malloc(bytes);
  if (audio == NULL) {
    mpg123_delete(handle);
    return 0;
  }

  mpg123_decode_frame_64(handle, &num, &audio, &bytes);

  free(audio);
  mpg123_delete(handle);
  return 0;
}