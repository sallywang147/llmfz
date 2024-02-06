#include <config.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../htslib/hts.h"
#include "../../htslib/sam.h"

extern "C" {
#include "../../htslib/kstring.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  uint8_t *copy = malloc(size);
  if (copy == NULL) {
    abort();
  }
  memcpy(copy, data, size);

  hFILE *memfile = hopen("mem:", "rb:", copy, size);
  if (memfile == NULL) {
    free(copy);
    return 0;
  }

  htsFile *in = hts_hopen(memfile, "data", "rb");
  if (in == NULL) {
    if (hclose(memfile) != 0)
      abort();
    return 0;
  }

  samFile *out = sam_open("/dev/null", "wb");
  if (!out)
    abort();

  bam_hdr_t *hdr = sam_hdr_read(in);
  if (hdr == NULL) {
    if (hclose(memfile) != 0)
      abort();
    hts_close(out);
    return 0;
  }

  // This will force the header to be parsed.
  (void)sam_hdr_count_lines(hdr, "SQ");

  if (sam_hdr_write(out, hdr) != 0)
    goto err;

  bam1_t *b = bam_init1();
  if (b == NULL)
    goto err;

  while (sam_read1(in, hdr, b) >= 0) {
    if (sam_write1(out, hdr, b) < 0)
      break;
  }
  bam_destroy1(b);

  if (hts_close(in) != 0)
    abort();

  if (hts_close(out) != 0)
    abort();

  char *fn = malloc(size);
  if (fn == NULL) {
    abort();
  }
  memcpy(fn, data, size);

  // This will force the header to be parsed.
  (void)sam_hdr_count_lines(hdr, "SQ");

  int min_shift = 0;
  if (bam_index_build2(fn, hdr, min_shift) != 0) // Change bam_index_build to bam_index_build2
    abort();

  free(fn);
  sam_hdr_destroy(hdr);
  return 0;

err:
  sam_hdr_destroy(hdr);
  if (hts_close(in) != 0)
    abort();
  if (hts_close(out) != 0)
    abort();
  return 0;
}