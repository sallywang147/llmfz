#include <fuzzer/FuzzedDataProvider.h>
#include <gssapi/gssapi.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare parameters for gss_accept_sec_context
  int minor_status = 0;
  gss_ctx_id_t context_handle = GSS_C_NO_CONTEXT;
  gss_cred_id_t acceptor_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_name_t src_name = GSS_C_NO_NAME;
  gss_OID_desc mech_type;
  int ret_flags = 0;
  int time_rec = 0;
  gss_cred_id_t delegated_cred_handle = GSS_C_NO_CREDENTIAL;

  // Consume data for input_token_buffer
  size_t input_token_buffer_size = stream.ConsumeIntegralInRange<size_t>(0, 50);
  std::vector<uint8_t> input_token_buffer_data = stream.ConsumeBytes<uint8_t>(input_token_buffer_size);
  gss_buffer_desc input_token_buffer = {input_token_buffer_size, input_token_buffer_data.data()};

  // Consume data for input_chan_bindings
  gss_channel_bindings_t input_chan_bindings;
  if (stream.remaining_bytes() >= sizeof(gss_channel_bindings_struct)) {
    input_chan_bindings = reinterpret_cast<gss_channel_bindings_t>(stream.ConsumeBytes<uint8_t>(sizeof(gss_channel_bindings_struct)).data());
  } else {
    input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;
  }

  // Prepare output_token
  gss_buffer_desc output_token = {0, nullptr};

  // Call gss_accept_sec_context
  gss_accept_sec_context(&minor_status, &context_handle, acceptor_cred_handle, &input_token_buffer, input_chan_bindings, &src_name, &mech_type, &output_token, &ret_flags, &time_rec, &delegated_cred_handle);

  // Clean up
  OM_uint32 tmp_status;
  if (context_handle != GSS_C_NO_CONTEXT) {
    gss_delete_sec_context(&tmp_status, &context_handle, GSS_C_NO_BUFFER);
  }
  if (src_name != GSS_C_NO_NAME) {
    gss_release_name(&tmp_status, &src_name);
  }
  if (delegated_cred_handle != GSS_C_NO_CREDENTIAL) {
    gss_release_cred(&tmp_status, &delegated_cred_handle);
  }
  if (output_token.length > 0) {
    gss_release_buffer(&tmp_status, &output_token);
  }

  return 0;
}