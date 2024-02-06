#include "libcue.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Cd cd;
  cd_init(&cd);
  cd_parse(&cd, data, size);
  cd_dump(&cd);
  cd_free(&cd);
  return 0;
}