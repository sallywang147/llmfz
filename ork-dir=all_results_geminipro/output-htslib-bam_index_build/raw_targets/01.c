#include <config.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <htslib/hts.h>
#include <htslib/sam.h>

static void bam_index_build_or_abort(char *fn, int min_shift) {
  if (bam_index_build(fn, min_shift) != 0) {
    fprintf(stderr, "bam_index_build: %s\n", strerror(errno));
    abort();
  }
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));
  char *fn = str.c_str();

  int min_shift = stream.ConsumeIntegralInRange(0, 255);

  bam_index_build_or_abort(fn, min_shift);
  return 0;
}