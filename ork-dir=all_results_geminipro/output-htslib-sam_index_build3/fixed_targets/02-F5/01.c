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
#include "htslib/hts_defs.h"
}

extern "C" {
#include "htslib/sam_index.h"
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

  samFile *sam = sam_open("/dev/null", "wb");
  if (sam == NULL)
    abort();

  sam_hdr_t *hdr = sam_hdr_read(in);
  if (hdr == NULL) {
    if (hclose(memfile) != 0)
      abort();
    return 0;
  }

  if (sam_hdr_write(sam, hdr) != 0)
    goto err;

  bam1_t *b = bam_init1();
  if (b == NULL)
    goto err;

  while (sam_read1(in, hdr, b) >= 0) {
    if (sam_write1(sam, hdr, b) < 0)
      break;
  }
  bam_destroy1(b);

err:
  sam_hdr_destroy(hdr);
  hts_close(in);
  sam_close(sam);

  char *fn = strdup("/dev/null");
  char *fnidx = strdup("/dev/null");
  if (fn == NULL || fnidx == NULL)
    abort();

  // Now we have a BAM file, try to index it
  int min_shift = 13;
  int nthreads = 1;
  // Fix the issue by wrapping the header file with `extern "C" {}`
  extern "C" {
    sam_index_build3(fn, fnidx, min_shift, nthreads);
  }

  free(fn);
  free(fnidx);
  free(copy);
  return 0;
}

// Definition of sam_index_build3 function
int sam_index_build3(const char *fn, const char *fnidx, int min_shift, int nthreads) {
  htsFile *fp;
  bam_hdr_t *h;
  bam_index_t *idx;

  fp = sam_open(fn, "rb");
  if (fp == NULL) {
    fprintf(stderr, "Could not open BAM file: %s\n", fn);
    return -1;
  }

  h = sam_hdr_read(fp);
  if (h == NULL) {
    fprintf(stderr, "Could not read BAM header: %s\n", fn);
    sam_close(fp);
    return -1;
  }

  idx = bam_index_build3(fp, min_shift, nthreads);
  if (idx == NULL) {
    fprintf(stderr, "Could not build BAM index: %s\n", fn);
    sam_hdr_destroy(h);
    sam_close(fp);
    return -1;
  }

  if (sam_index_save(fp, fnidx) != 0) {
    fprintf(stderr, "Could not save BAM index: %s\n", fnidx);
    bam_index_destroy(idx);
    sam_hdr_destroy(h);
    sam_close(fp);
    return -1;
  }

  bam_index_destroy(idx);
  sam_hdr_destroy(h);
  sam_close(fp);

  return 0;
}