#include "libcue.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "cd_track_dump.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Track *track = cd_track_new_from_data(data, size);
  if (track == NULL) {
    return 0;
  }
  cd_track_dump(track);
  cd_track_free(track);
  return 0;
}