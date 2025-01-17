#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <gssapi/gssapi.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();

  gss_ctx_id_t context_handle = GSS_C_NO_CONTEXT;
  gss_cred_id_t verifier_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
  gss_channel_bindings_struct input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;
  gss_name_t src_name = GSS_C_NO_NAME;
  gss_OID_desc_struct mech_type = GSS_C_NO_OID;
  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
  int ret_flags;
  int time_rec;
  gss_cred_id_t delegated_cred_handle = GSS_C_NO_CREDENTIAL;

  int minor_status;
  const std::string text = stream.ConsumeRemainingBytesAsString();
  input_token.length = text.size();
  input_token.value = const_cast<char*>(text.c_str());

  iakerb_gss_accept_sec_context(&minor_status, &context_handle,
                               verifier_cred_handle, &input_token,
                               &input_chan_bindings, &src_name, &mech_type,
                               &output_token, &ret_flags, &time_rec,
                               &delegated_cred_handle);

  gss_release_buffer(&minor_status, &input_token);
  gss_release_buffer(&minor_status, &output_token);
  gss_release_name(&minor_status, &src_name);
  gss_release_oid(&minor_status, &mech_type);
  gss_release_cred(&minor_status, &verifier_cred_handle);
  gss_release_cred(&minor_status, &delegated_cred_handle);
  gss_delete_sec_context(&minor_status, &context_handle, GSS_C_NO_BUFFER);
  return 0;
}