#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "mpg123.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    mpg123_init();
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  int error;
  mpg123_handle *mh = mpg123_new(NULL, &error);
  if (mh == NULL) {
    return 0;
  }

  if (mpg123_open_feed(mh) != MPG123_OK) {
    mpg123_delete(mh);
    return 0;
  }

  size_t feed_size = stream.remaining_bytes() / 2;
  if (mpg123_feed(mh, stream.data(), feed_size) != MPG123_OK) {
    mpg123_close(mh);
    mpg123_delete(mh);
    return 0;
  }

  size_t num;
  char *audio;
  size_t bytes;
  mpg123_decode_frame(mh, &num, &audio, &bytes);

  mpg123_close(mh);
  mpg123_delete(mh);

  return 0;
}