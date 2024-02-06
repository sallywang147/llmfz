#include <string.h>

#include "gss_ntlmssp.h"
extern "C" {
#include <gssapi.h>
#include <krb5.h>
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  OM_uint32 maj_stat, min_stat;

  gss_cred_id_t claimant_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_ctx_id_t context_handle = GSS_C_NO_CONTEXT;
  gss_name_t target_name = GSS_C_NO_NAME;
  gss_OID_desc_struct mech_type = GSS_C_NULL_OID;
  struct gss_channel_bindings_struct input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;
  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
  gss_OID_desc_struct *actual_mech_type = NULL;
  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
  int ret_flags = 0;
  int time_rec = 0;

  maj_stat = gssntlm_init_sec_context(&min_stat, &claimant_cred_handle,
                                      &context_handle, target_name, &mech_type, 0,
                                      0, &input_chan_bindings, &input_token,
                                      &actual_mech_type, &output_token, &ret_flags,
                                      &time_rec);

  gss_release_buffer(&min_stat, &input_token);
  gss_release_buffer(&min_stat, &output_token);

  gss_delete_sec_context(&min_stat, &context_handle, NULL);

  return 0;
}