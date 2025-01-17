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
  VIO_DATA vio_data;
  SF_VIRTUAL_IO vio;
  SNDFILE *sndfile = NULL;
  int err = sf_open_virtual(&vio, SFM_READ, &sndfile_info, &vio_data, data, size, &sndfile);
  if (err)
    goto EXIT_LABEL;

  double max_val = psf_calc_signal_max(sndfile->priv, decider % 2);

EXIT_LABEL:
  if (sndfile != NULL)
    sf_close(sndfile);

  return 0;
}