#include <string.h>

#include "gssapi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  OM_uint32 maj_stat, min_stat;

  gss_cred_id_t claimant_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_ctx_id_t context_handle = GSS_C_NO_CONTEXT;
  gss_name_t target_name = GSS_C_NO_NAME;
  gss_OID_desc_struct mech_type = {0, 0};
  int req_flags = 0;
  int time_req = 0;
  gss_channel_bindings_struct input_chan_bindings = {0, 0};
  gss_buffer_desc_struct input_token = {0, 0};
  gss_OID_desc_struct *actual_mech_type = 0;
  gss_buffer_desc_struct output_token = {0, 0};
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

    maj_stat = gss_init_sec_context(&min_stat, claimant_cred_handle, &context_handle,
                                    target_name, &mech_type, req_flags, time_req,
                                    &input_chan_bindings, &input_token,
                                    &actual_mech_type, &output_token, &ret_flags,
                                    &time_rec);

    if (maj_stat == GSS_S_CONTINUE_NEEDED) {
      gss_release_buffer(&min_stat, &input_token);
      gss_release_buffer(&min_stat, &output_token);
      free(input_token.value);
    }
  } while (maj_stat == GSS_S_CONTINUE_NEEDED);

  gss_delete_sec_context(&min_stat, &context_handle, GSS_C_NO_BUFFER);

  return 0;
}
```

The issue is that the `gss_release_buffer` function is called for the `input_token` and `output_token` buffers even when the `maj_stat` is not `GSS_S_CONTINUE_NEEDED`. This is incorrect, as the buffers should only be released when the context is successfully established (i.e., when `maj_stat` is `GSS_S_COMPLETE`).

To fix the issue, the `gss_release_buffer` calls should be moved inside the `if (maj_stat == GSS_S_CONTINUE_NEEDED)` block. This ensures that the buffers are only released when the context is successfully established.