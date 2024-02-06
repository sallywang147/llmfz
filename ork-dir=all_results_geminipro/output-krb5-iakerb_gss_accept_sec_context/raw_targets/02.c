#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <string>

#include <gssapi/gssapi.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int minor_status;
  gss_ctx_id_struct* context_handle = nullptr;
  gss_cred_id_struct* verifier_cred_handle = nullptr;
  gss_buffer_desc_struct input_token;
  input_token.length = stream.ConsumeIntegral<size_t>();
  input_token.value = stream.ConsumeBytes<uint8_t>(input_token.length).data();
  gss_channel_bindings_struct* input_chan_bindings = nullptr;
  gss_name_struct* src_name = nullptr;
  gss_OID_desc_struct* mech_type = nullptr;
  gss_buffer_desc_struct output_token;
  output_token.length = 0;
  output_token.value = nullptr;
  int ret_flags;
  int time_rec;
  gss_cred_id_struct* delegated_cred_handle = nullptr;

  iakerb_gss_accept_sec_context(&minor_status, &context_handle,
                               verifier_cred_handle, &input_token,
                               input_chan_bindings, &src_name, &mech_type,
                               &output_token, &ret_flags, &time_rec,
                               &delegated_cred_handle);

  gss_release_buffer(&minor_status, &output_token);

  return 0;
}