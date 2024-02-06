#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <gssapi/gssapi.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize variables.
  int minor_status = 0;
  gss_ctx_id_t context_handle = GSS_C_NO_CONTEXT;
  gss_cred_id_t acceptor_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_buffer_desc input_token_buffer;
  input_token_buffer.length = 0;
  input_token_buffer.value = nullptr;
  gss_channel_bindings_struct input_chan_bindings;
  input_chan_bindings.initiator_addrtype = 0;
  input_chan_bindings.initiator_address.length = 0;
  input_chan_bindings.initiator_address.value = nullptr;
  input_chan_bindings.acceptor_addrtype = 0;
  input_chan_bindings.acceptor_address.length = 0;
  input_chan_bindings.acceptor_address.value = nullptr;
  input_chan_bindings.application_data.length = 0;
  input_chan_bindings.application_data.value = nullptr;
  gss_name_t src_name = GSS_C_NO_NAME;
  gss_OID_desc_struct* mech_type = nullptr;
  gss_buffer_desc output_token_buffer;
  output_token_buffer.length = 0;
  output_token_buffer.value = nullptr;
  int ret_flags = 0;
  int time_rec = 0;
  gss_cred_id_t delegated_cred_handle = GSS_C_NO_CREDENTIAL;

  // Consume input data.
  std::string input_token = stream.ConsumeRemainingBytesAsString();
  input_token_buffer.length = input_token.size();
  input_token_buffer.value = const_cast<char*>(input_token.c_str());

  // Call gss_accept_sec_context.
  gss_accept_sec_context(&minor_status, &context_handle, acceptor_cred_handle,
                         &input_token_buffer, &input_chan_bindings, &src_name,
                         &mech_type, &output_token_buffer, &ret_flags, &time_rec,
                         &delegated_cred_handle);

  // Clean up.
  gss_release_buffer(&minor_status, &input_token_buffer);
  gss_release_buffer(&minor_status, &output_token_buffer);
  gss_release_name(&minor_status, &src_name);
  gss_release_cred(&minor_status, &acceptor_cred_handle);
  gss_release_cred(&minor_status, &delegated_cred_handle);
  gss_delete_sec_context(&minor_status, &context_handle, GSS_C_NO_BUFFER);

  return 0;
}