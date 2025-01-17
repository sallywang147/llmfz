#include <inttypes.h>
#include <sndfile.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "sndfile_fuzz_header.h"

extern "C" {
#include <psflib.h>
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
  double *peaks_buffer = NULL;
  peaks_buffer = (double *)malloc(sizeof(double) * sndfile_info.channels);
  if (peaks_buffer == NULL)
    abort();

  psf_calc_max_all_channels(sndfile->private_data, peaks_buffer, decider % 2);

  free(peaks_buffer);

EXIT_LABEL:
  if (sndfile != NULL)
    sf_close(sndfile);

  return 0;
}
```

In this case, the error is:

```
error: undefined reference to `psf_calc_max_all_channels'
```

This error means that the linker cannot find the definition of the function `psf_calc_max_all_channels`. This function is declared in the header file `psflib.h`, but it is not defined in any of the source files that are being linked. To fix this error, you need to add the source file that defines the function `psf_calc_max_all_channels` to the build.

In this case, the source file that defines the function `psf_calc_max_all_channels` is `psflib.c`. To add this file to the build, you need to add the following line to the Makefile:

```
SRC += psflib.c
```

Once you have added this line to the Makefile, you should be able to build the program successfully.