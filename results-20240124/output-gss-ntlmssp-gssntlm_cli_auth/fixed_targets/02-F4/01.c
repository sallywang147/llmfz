#include <iostream>

extern "C" {
#include <gssntlm.h>
}

extern "C" {
#include <ntlm.h>
}

int main() {
  gssntlm_ctx_handle_t ctx = nullptr;
  gssntlm_cred_handle_t cred = nullptr;

  // Initialize the NTLM context
  gssntlm_init_ctx(&ctx);

  // Initialize the NTLM credentials
  gssntlm_init_cred(&cred);

  // Perform NTLM client authentication
  gssntlm_cli_auth(ctx, cred);

  // Free the NTLM context
  gssntlm_free_ctx(ctx);

  // Free the NTLM credentials
  gssntlm_free_cred(cred);

  return 0;
}