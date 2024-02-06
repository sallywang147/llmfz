#include <cstdint>
#include <cstdlib>
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
  FuzzedDataProvider stream(data, size);

  xvid_enc_create_t ctx;
  xvid_enc_frame_t frame;

  uint32_t width = 0;
  uint32_t height = 0;

  uint8_t *out = nullptr;
  uint8_t *inptr = nullptr;
  uint8_t *dataCopy = (uint8_t *)calloc(1, size + 10240);
  memcpy(dataCopy, data, size);

  inptr = dataCopy;

  {
    memset(&ctx, 0, sizeof(ctx));

    ctx.version = XVID_VERSION;
    ctx.width = width;
    ctx.height = height;
  }

  if (xvid_encore(nullptr, XVID_ENC_CREATE, &ctx, nullptr)) {
    abort();
  }

  {
    memset(&frame, 0, sizeof(xvid_enc_frame_t));

    frame.version = XVID_VERSION;
    frame.general = 0;

    frame.input.plane[0] = inptr;
    frame.input.stride[0] = width * 3;

    frame.output.plane[0] = out;
    frame.output.stride[0] = width * 3;

    frame.input.csp = XVID_CSP_BGR;
    frame.output.csp = XVID_CSP_BGR;
  }

  xvid_encore(ctx.handle, XVID_ENC_ENCODE, &frame, nullptr);

  free(dataCopy);
  free(out);

  xvid_encore(ctx.handle, XVID_ENC_DESTROY, nullptr, nullptr);
  return 0;
}