#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "src/vlm/vlm.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libvlc/libvlc.h>
}

int LLVMFuzzerInitialize(int *argc, char ***argv);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

static struct libvlc_int_t libvlc;
static struct vlm_t *vlm;

int LLVMFuzzerInitialize(int *argc, char ***argv) {
  (void)argc;
  (void)argv;

  vlc_libvlc_int_init(&libvlc);

  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  vlm = vlm_New(&libvlc, NULL);
  if (vlm == NULL) {
    return 0;
  }

  vlm_AddBuffer(vlm, data, size);
  vlm_Parse(vlm);

  vlm_Delete(vlm);
  return 0;
}