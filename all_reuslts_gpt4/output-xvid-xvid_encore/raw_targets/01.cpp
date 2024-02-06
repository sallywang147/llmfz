#include <cstdint>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <xvid.h>
#include <fuzzer/FuzzedDataProvider.h>

xvid_gbl_init_t glb;

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
  memset(&glb, 0, sizeof(glb));
  glb.version = XVID_VERSION;
  if (xvid_global(nullptr, XVID_GBL_INIT, &glb, nullptr)) {
    abort();
  }

  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  xvid_enc_create_t create;
  xvid_enc_frame_t frame;
  xvid_enc_stats_t stats;

  memset(&create, 0, sizeof(create));
  create.version = XVID_VERSION;
  create.width = stream.ConsumeIntegralInRange<int>(1, 1280);
  create.height = stream.ConsumeIntegralInRange<int>(1, 720);

  if (xvid_encore(nullptr, XVID_ENC_CREATE, &create, nullptr)) {
    abort();
  }

  memset(&frame, 0, sizeof(frame));
  frame.version = XVID_VERSION;
  frame.input.plane[0] = stream.ConsumeRemainingBytes().data();
  frame.input.csp = XVID_CSP_I420;
  frame.input.stride[0] = create.width;

  xvid_encore(create.handle, XVID_ENC_ENCODE, &frame, &stats);

  xvid_encore(create.handle, XVID_ENC_DESTROY, nullptr, nullptr);

  return 0;
}