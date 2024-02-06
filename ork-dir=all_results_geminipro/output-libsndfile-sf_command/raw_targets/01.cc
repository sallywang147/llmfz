#include <inttypes.h>
#include <sndfile.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "sndfile_fuzz_header.h"

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
    char *write_buffer = NULL;
    write_buffer = (char *)malloc(sizeof(char) * size);
    if (write_buffer == NULL)
      abort();

    sf_command(sndfile, SFC_GET_INSTRUMENT, write_buffer, size);
    free(write_buffer);
  } break;
  case 1: {
    char *write_buffer = NULL;
    write_buffer = (char *)malloc(sizeof(char) * size);
    if (write_buffer == NULL)
      abort();

    sf_command(sndfile, SFC_GET_LIB_VERSION, write_buffer, size);
    free(write_buffer);
  } break;
  case 2: {
    char *write_buffer = NULL;
    write_buffer = (char *)malloc(sizeof(char) * size);
    if (write_buffer == NULL)
      abort();

    sf_command(sndfile, SFC_GET_FORMAT_INFO, write_buffer, size);
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