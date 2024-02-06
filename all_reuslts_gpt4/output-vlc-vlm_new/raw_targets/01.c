#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "src/libvlccore/vlm.h"
#include "src/libvlccore/vlc.h"

int LLVMFuzzerInitialize(int *argc, char ***argv);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

static libvlc_int_t *libvlc;

int LLVMFuzzerInitialize(int *argc, char ***argv) {
  (void)argc;
  (void)argv;

  libvlc = libvlc_InternalCreate();
  if (libvlc == NULL) {
    return -1;
  }

  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char* psz_vlmconf = reinterpret_cast<char*>(malloc(size + 1));
  if (!psz_vlmconf) {
    return 0;
  }
  memcpy(psz_vlmconf, data, size);
  psz_vlmconf[size] = '\0';

  struct vlm_t* vlm = vlm_New(libvlc, psz_vlmconf);
  if (vlm != NULL) {
    vlm_Delete(vlm);
  }

  free(psz_vlmconf);

  return 0;
}