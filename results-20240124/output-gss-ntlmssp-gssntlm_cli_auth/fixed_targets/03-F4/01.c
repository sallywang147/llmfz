#include "gssntlm.h"
#include <stddef.h>

extern "C" {
#include <gssapi/gssapi.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  gssntlm_ctx *ctx = gssntlm_alloc_ctx();
  struct gssntlm_cred *cred = NULL;
  struct ntlm_buffer *target_info = NULL;
  int in_flags = 0;
  struct gss_channel_bindings_struct *input_chan_bindings = NULL;
  int minor_status;

  gssntlm_cli_auth(&minor_status, ctx, cred, target_info, in_flags, input_chan_bindings);

  gssntlm_free_ctx(ctx);
  return 0;
}