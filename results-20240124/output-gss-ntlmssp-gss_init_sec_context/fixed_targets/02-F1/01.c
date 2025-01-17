#include <gssapi/gssapi_ext.h>
#include <stddef.h>

extern "C" {
#include <gssapi/gssapi.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Fix the code by calling the target function inside the fuzzer function.
  int minor_status;
  struct gss_cred_id_struct *claimant_cred_handle = NULL;
  struct gss_ctx_id_struct *context_handle = NULL;
  struct gss_name_struct *target_name = NULL;
  struct gss_OID_desc_struct *mech_type = NULL;
  int req_flags = 0;
  int time_req = 0;
  struct gss_channel_bindings_struct *input_chan_bindings = NULL;
  struct gss_buffer_desc_struct input_token = {0};
  struct gss_OID_desc_struct *actual_mech_type = NULL;
  struct gss_buffer_desc_struct output_token = {0};
  int ret_flags = 0;
  int time_rec = 0;

  // Set the input token data.
  input_token.length = size;
  input_token.value = (void *)data;

  // Call the target function.
  gss_init_sec_context(&minor_status, claimant_cred_handle, &context_handle,
                        target_name, mech_type, req_flags, time_req,
                        input_chan_bindings, &input_token, &actual_mech_type,
                        &output_token, &ret_flags, &time_rec);

  // Free the allocated memory.
  if (context_handle != NULL) {
    gss_delete_sec_context(&minor_status, &context_handle, NULL);
  }
  if (output_token.value != NULL) {
    gss_release_buffer(&minor_status, &output_token);
  }

  return 0;
}