#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <gssapi/gssapi.h>

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gss_cred_id_t claimant_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_ctx_id_t* context_handle = nullptr;
  gss_name_t target_name = GSS_C_NO_NAME;
  gss_OID_desc_struct* mech_type = nullptr;
  int req_flags = stream.ConsumeIntegral<int>();
  int time_req = stream.ConsumeIntegral<int>();
  gss_channel_bindings_struct* input_chan_bindings = nullptr;
  gss_buffer_desc_struct input_token = GSS_C_EMPTY_BUFFER;
  gss_OID_desc_struct** actual_mech_type = nullptr;
  gss_buffer_desc_struct output_token = GSS_C_EMPTY_BUFFER;
  int* ret_flags = nullptr;
  int* time_rec = nullptr;

  OM_uint32 minor_status;
  OM_uint32 major_status =
      gss_init_sec_context(&minor_status, claimant_cred_handle,
                                 &context_handle, target_name, mech_type, req_flags,
                                 time_req, input_chan_bindings, &input_token,
                                 actual_mech_type, &output_token, ret_flags,
                                 time_rec);
  if (GSS_ERROR(major_status)) {
    return 0;
  }

  gss_release_buffer(&minor_status, &output_token);

  return 0;
}

int krb5_gss_init_sec_context(
    int *minor_status, struct gss_cred_id_struct *claimant_cred_handle,
    struct gss_ctx_id_struct **context_handle, struct gss_name_struct *target_name,
    struct gss_OID_desc_struct *mech_type, int req_flags, int time_req,
    struct gss_channel_bindings_struct *input_chan_bindings,
    struct gss_buffer_desc_struct *input_token,
    struct gss_OID_desc_struct **actual_mech_type,
    struct gss_buffer_desc_struct *output_token, int *ret_flags, int *time_rec) {
  return 0;
}
}