#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

#include "src/input/vlm.h"

int LLVMFuzzerInitialize(int *argc, char ***argv);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

static struct libvlc_int_t *libvlc;

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
  FuzzedDataProvider stream(data, size);
  std::string vlmconf = stream.ConsumeRemainingBytesAsString();
  struct vlm_t *vlm = vlm_New(libvlc, vlmconf.c_str());
  if (vlm != NULL) {
    vlm_Delete(vlm);
  }
  return 0;
}