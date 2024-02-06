#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <gssapi/gssapi.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int minor_status = stream.ConsumeIntegral<int>();
  const gss_cred_id_struct claimant_cred_handle =
      GSS_C_NO_CREDENTIAL;  // TODO(b/230451788): Fuzz this value.
  gss_ctx_id_struct* context_handle = nullptr;
  const gss_name_struct target_name = GSS_C_NO_NAME;  // TODO(b/230451788): Fuzz this value.
  const gss_OID_desc_struct mech_type = GSS_C_NULL_OID;  // TODO(b/230451788): Fuzz this value.
  const int req_flags = stream.ConsumeIntegral<int>();
  const int time_req = stream.ConsumeIntegral<int>();
  const gss_channel_bindings_struct input_chan_bindings =
      GSS_C_NO_CHANNEL_BINDINGS;  // TODO(b/230451788): Fuzz this value.
  const gss_buffer_desc_struct input_token = GSS_C_EMPTY_BUFFER;  // TODO(b/230451788): Fuzz this value.
  gss_OID_desc_struct* actual_mech_type = nullptr;
  gss_buffer_desc_struct output_token = GSS_C_EMPTY_BUFFER;
  int ret_flags = 0;
  int time_rec = 0;

  const int result = iakerb_gss_init_sec_context(
      &minor_status, &claimant_cred_handle, &context_handle, &target_name,
      &mech_type, req_flags, time_req, &input_chan_bindings, &input_token,
      &actual_mech_type, &output_token, &ret_flags, &time_rec);
  if (result != GSS_S_COMPLETE) {
    return 0;
  }

  gss_release_buffer(&minor_status, &output_token);
  return 0;
}