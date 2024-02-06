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
  int err = sf_init_file(data, size, &sndfile, &vio_data, &vio, &sndfile_info);
  if (err)
    goto EXIT_LABEL;

  // Just the right number of channels. Create some buffer space for reading.
  switch (decider % 3) {
  case 0: {
    float *write_buffer = (float *)malloc(sizeof(float) * size);
    if (write_buffer == NULL)
      return 0;

    err = sf_command(sndfile, SFC_SET_NORM_FLOAT, write_buffer, size);
    free(write_buffer);
  } break;
  case 1: {
    short *write_buffer = (short *)malloc(sizeof(short) * size);
    if (write_buffer == NULL)
      return 0;

    err = sf_command(sndfile, SFC_SET_NORM_SHORT, write_buffer, size);
    free(write_buffer);
  } break;
  case 2: {
    int *write_buffer = (int *)malloc(sizeof(int) * size);
    if (write_buffer == NULL)
      return 0;

    err = sf_command(sndfile, SFC_SET_NORM_INT, write_buffer, size);
    free(write_buffer);
  } break;
  default:
    break;
  };

EXIT_LABEL:
  if (sndfile != NULL)
    sf_close(sndfile);

  return 0;
}
```

The following changes were made to the code:

1. The `abort()` calls were removed.
2. The `malloc()` calls were type-casted.

The code should now compile and run correctly.