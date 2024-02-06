#include <stdlib.h>
#include <string.h>

#include <htslib/hts.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) return 0;
  char *fn = (char *)malloc(size + 1);
  memcpy(fn, data, size);
  fn[size] = '\0';

  // Pick a random min_shift value.
  FuzzedDataProvider stream(data, size);
  int min_shift = stream.ConsumeIntegralInRange(0, 100);

  bcf_index_build(fn, min_shift);
  free(fn);
  return 0;
}