#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <gssapi.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int minor_status = 0;
  gss_cred_id_struct* claimant_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_ctx_id_struct** context_handle = nullptr;
  gss_name_struct* target_name = GSS_C_NO_NAME;
  gss_OID_desc_struct* mech_type = GSS_C_NO_OID;
  int req_flags = stream.ConsumeIntegral<int>();
  int time_req = stream.ConsumeIntegral<int>();
  gss_channel_bindings_struct* input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;
  gss_buffer_desc_struct input_token = GSS_C_EMPTY_BUFFER;
  gss_OID_desc_struct** actual_mech_type = nullptr;
  gss_buffer_desc_struct output_token = GSS_C_EMPTY_BUFFER;
  int* ret_flags = nullptr;
  int* time_rec = nullptr;

  const std::string input_token_bytes = stream.ConsumeRemainingBytesAsString();
  input_token.length = input_token_bytes.size();
  input_token.value = const_cast<char*>(input_token_bytes.c_str());

  iakerb_gss_init_sec_context(&minor_status, claimant_cred_handle, context_handle,
                             target_name, mech_type, req_flags, time_req,
                             input_chan_bindings, &input_token, actual_mech_type,
                             &output_token, ret_flags, time_rec);
  gss_release_buffer(&minor_status, &output_token);
  return 0;
}