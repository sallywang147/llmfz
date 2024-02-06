#include <inttypes.h>
#include <sndfile.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "sndfile_fuzz_header.h"

extern "C" {
#include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) { // One byte is needed for deciding which function to target.
  if (size == 0)
    return 0;

  const uint8_t decider = *data;
  data += 1;
  size -= 1;

  SF_INFO sndfile_info;
  SNDFILE *sndfile = NULL;
  int err = sf_open_fd(decider % 2, decider % 3, &sndfile_info, SFM_READ, decider % 2);
  if (err)
    goto EXIT_LABEL;

  while (sf_read_short(sndfile, NULL, size, SF_COUNT_MAX)) {
    // Do nothing with the data.
  }

EXIT_LABEL:
  if (sndfile != NULL)
    sf_close(sndfile);

  return 0;
}