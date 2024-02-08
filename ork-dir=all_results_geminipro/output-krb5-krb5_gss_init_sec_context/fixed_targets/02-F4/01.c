#include <string.h>

#include "gssapi.h"
#include "krb5.h"

extern "C" {
#include <krb5/gssapi.h>
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  OM_uint32 maj_stat, min_stat;

  gss_cred_id_t claimant_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_ctx_id_t context_handle = GSS_C_NO_CONTEXT;
  gss_name_t target_name = GSS_C_NO_NAME;
  gss_OID_desc_struct mech_type = {0, 0};
  gss_channel_bindings_struct input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;
  gss_buffer_desc_struct input_token = GSS_C_EMPTY_BUFFER;
  gss_OID_desc_struct *actual_mech_type = NULL;
  gss_buffer_desc_struct output_token = GSS_C_EMPTY_BUFFER;
  int ret_flags = 0;
  int time_rec = 0;

  /* Each fuzz input contains multiple tokens preceded by a length field.
   * Process them in turn with gss_init_sec_context while
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

    maj_stat = krb5_gss_init_sec_context(&min_stat, claimant_cred_handle,
                                    &context_handle, target_name, &mech_type,
                                    0, 0, &input_chan_bindings, &input_token,
                                    &actual_mech_type, &output_token, &ret_flags,
                                    &time_rec);

    gss_release_buffer(&min_stat, &output_token);
    free(input_token.value);

    if (GSS_ERROR(maj_stat)) {
      if (context_handle != GSS_C_NO_CONTEXT)
        gss_delete_sec_context(&min_stat, &context_handle, GSS_C_NO_BUFFER);
      break;
    }
  } while (maj_stat & GSS_S_CONTINUE_NEEDED);

  if (context_handle != GSS_C_NO_CONTEXT)
    gss_delete_sec_context(&min_stat, &context_handle, GSS_C_NO_BUFFER);
  gss_release_name(&min_stat, &target_name);

  return 0;
}