#include <gssntlmssp.h>

extern "C" {
#include <gssntlmssp.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Fix the build error by calling the function `gssntlm_cli_auth` inside the function `LLVMFuzzerTestOneInput`.
  int minor_status;
  struct gssntlm_ctx ctx;
  struct gssntlm_cred cred;
  struct ntlm_buffer target_info;
  int in_flags;
  struct gss_channel_bindings_struct input_chan_bindings;

  gssntlm_cli_auth(&minor_status, &ctx, &cred, &target_info, in_flags, &input_chan_bindings);

  return 0;
}