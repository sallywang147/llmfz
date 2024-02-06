#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>

#include <xvid.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  xvid_enc_create_t ctx;
  xvid_enc_frame_t frame;
  xvid_enc_stats_t stats;

  memset(&ctx, 0, sizeof(ctx));
  ctx.version = XVID_VERSION;
  ctx.width = 320;
  ctx.height = 240;
  ctx.profile = XVID_PROFILE_SIMPLE;

  if (xvid_encore(nullptr, XVID_ENC_CREATE, &ctx, nullptr)) {
    abort();
  }

  memset(&frame, 0, sizeof(frame));
  frame.version = XVID_VERSION;
  frame.input.plane[0] = (uint8_t *)data;
  frame.input.stride[0] = 320;
  frame.input.csp = XVID_CSP_BGR;

  memset(&stats, 0, sizeof(stats));
  stats.version = XVID_VERSION;

  // Call the enc_encode function to encode the frame
  xvid_encore(&ctx.handle, XVID_ENC_ENCODE, &frame, &stats);

  xvid_encore(ctx.handle, XVID_ENC_DESTROY, nullptr, nullptr);

  return 0;
}