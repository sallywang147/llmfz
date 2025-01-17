#include <config.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../htslib/hfile.h"
#include "../../htslib/hts.h"
#include "../../htslib/sam.h"

static void hts_close_or_abort(htsFile *file) {
  if (hts_close(file) != 0) {
    abort();
  }
}

static void view_sam(const uint8_t *data, size_t size, char *mode, int close_abort) {
  uint8_t *copy = malloc(size);
  if (copy == NULL) {
    abort();
  }
  memcpy(copy, data, size);

  hFILE *memfile = hopen("mem:", "rb:", copy, size);
  if (memfile == NULL) {
    free(copy);
    return;
  }

  htsFile *in = hts_hopen(memfile, "data", "rb");
  if (in == NULL) {
    if (hclose(memfile) != 0)
      abort();
    return;
  }

  samFile *out = sam_open("/dev/null", mode);
  if (!out)
    abort();

#ifdef FUZZ_FAI
  // Not critical if this doesn't work, but can test more if
  // we're in the right location.
  //
  // We can't rely on what the pwd is for the OSS-fuzz so we don't enable
  // this by default.
  if (hts_set_fai_filename(out, "../c2.fa") < 0) {
    static int warned = 0;
    if (!warned) {
      warned = 1;
      fprintf(stderr, "Warning couldn't find the c2.fa file\n");
    }
  }
#endif

  sam_hdr_t *hdr = sam_hdr_read(in);
  if (hdr == NULL) {
    if (close_abort)
      hts_close_or_abort(out);
    else
      hts_close(out);
    hts_close(in);
    return;
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

err:
  sam_hdr_destroy(hdr);
  if (close_abort)
    hts_close_or_abort(out);
  else
    hts_close(out);
  hts_close(in);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *filename = stream.ConsumeRandomLengthString(1024);
  int min_shift = stream.ConsumeIntegral<int>();
  int ret = sam_index_build(filename, min_shift);
  free(filename);
  return ret;
}