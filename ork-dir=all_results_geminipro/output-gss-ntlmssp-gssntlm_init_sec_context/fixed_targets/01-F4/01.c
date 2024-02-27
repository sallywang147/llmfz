#include <gssapi/gssapi.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <gssntlm.h>
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  OM_uint32 maj_stat, min_stat;

  gss_cred_id_t client_cred = GSS_C_NO_CREDENTIAL;
  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gss_name_t target_name = GSS_C_NO_NAME;
  gss_OID_desc mech_type = GSS_C_NULL_OID;
  gss_OID_desc actual_mech_type = GSS_C_NULL_OID;
  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
  int req_flags = 0;
  int time_req = 0;
  int ret_flags = 0;
  int time_rec = 0;
  gss_channel_bindings_struct input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;

  /* Each fuzz input contains multiple tokens preceded by a length field.
   * Process them in turn with gss_accept_sec_context while
   * GSS_S_CONTINUE_NEEDED is set
   */
  do {
    unsigned short token_length;

    if (Size < sizeof(token_length))
      break;

    token_length = *(unsigned short *)Data;

    Data += sizeof(token_length);
    Size -= sizeof(token_length);

    if (token_length == 0 || token_length > Size)
      break;

    input_token.length = token_length;
    input_token.value = malloc(token_length);
    memcpy(input_token.value, Data, token_length);

    Data += token_length;
    Size -= token_length;

    maj_stat = gssntlm_init_sec_context(&min_stat, &client_cred, &ctx, target_name,
                                        &mech_type, req_flags, time_req,
                                        &input_chan_bindings, &input_token,
                                        &actual_mech_type, &output_token, &ret_flags,
                                        &time_rec);

    gss_release_buffer(&min_stat, &input_token);
    gss_release_buffer(&min_stat, &output_token);
  } while (maj_stat == GSS_S_CONTINUE_NEEDED);

  gss_release_name(&min_stat, &target_name);
  gss_release_cred(&min_stat, &client_cred);
  gss_release_oid(&min_stat, &mech_type);
  gss_release_oid(&min_stat, &actual_mech_type);

  gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);

  return 0;
}