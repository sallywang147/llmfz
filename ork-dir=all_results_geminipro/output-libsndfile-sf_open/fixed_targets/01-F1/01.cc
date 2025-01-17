#include <inttypes.h>
#include <sndfile.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "sndfile_fuzz_header.h"

extern "C" {
#include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  const uint8_t decider = *data;
  data += 1;
  size -= 1;

  SF_INFO sndfile_info;
  SNDFILE *sndfile = NULL;

  // Just the right number of channels. Create some buffer space for reading.
  switch (decider % 3) {
  case 0:
    sndfile = sf_open_mem(data, size, &sndfile_info, SFM_READ);
    break;
  case 1:
    sndfile = sf_open_fd(data[0], SFM_READ, &sndfile_info);
    break;
  case 2:
    sndfile = sf_open(reinterpret_cast<char *>(data), SFM_READ, &sndfile_info);
    break;
  default:
    break;
  };

  if (sndfile == NULL)
    goto EXIT_LABEL;

EXIT_LABEL:
  if (sndfile != NULL)
    sf_close(sndfile);

  return 0;
}