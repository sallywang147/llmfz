#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vlm.h"

struct libvlc_int_t *libvlc;

extern "C" {
#include <libvlc/libvlc.h>
}

int LLVMFuzzerInitialize(int *argc, char ***argv) {
  (void)argc;
  (void)argv;

  libvlc = libvlc_new(0, NULL);
  return libvlc ? 0 : -1;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t str_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  char *str = stream.ConsumeBytes<char>(str_size).data();
  vlm_New(libvlc, str);
  free(str);
  return 0;
}