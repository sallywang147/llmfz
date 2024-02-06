#include <config.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../hts/sam.h"

extern "C" {
#include "../../hts/hts.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  samFile *in;
  bam_hdr_t *h;
  char *fn;
  int min_shift = 0;

  if (size < 4) return 0;  /* need space for a SAM header */

  fn = strdup("/dev/shm/test.bam");
  in = sam_open(fn, "wb");
  if (in == 0) {
    perror(fn);
    return 1;
  }
  h = sam_hdr_read(in);
  sam_close(in);

  sam_index_build(fn, min_shift);

  sam_hdr_destroy(h);
  free(fn);

  return 0;
}