#include "libcue.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Track *track = cd_track_new();
  if (!track) {
    return 0;
  }
  cd_track_parse(track, data, size);
  cd_track_dump(track);
  cd_track_free(track);
  return 0;
}