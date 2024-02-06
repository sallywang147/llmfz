#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <gssapi/gssapi.h>

extern "C" {
#include <gssapi/gssapi_ext.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gss_cred_id_t acceptor_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_ctx_id_struct* context_handle = nullptr;
  gss_name_t src_name = GSS_C_NO_NAME;
  gss_OID_desc_struct* mech_type = nullptr;
  gss_buffer_desc_struct input_token_buffer;
  input_token_buffer.length = stream.ConsumeIntegral<size_t>();
  input_token_buffer.value = stream.ConsumeBytes<uint8_t>(input_token_buffer.length);
  gss_channel_bindings_struct* input_chan_bindings = nullptr;
  gss_buffer_desc_struct output_token;
  int minor_status;
  int* ret_flags = nullptr;
  int* time_rec = nullptr;
  gss_cred_id_struct* delegated_cred_handle = nullptr;

  auto result = gss_accept_sec_context(
      &minor_status, &context_handle, acceptor_cred_handle, &input_token_buffer,
      input_chan_bindings, &src_name, &mech_type, &output_token, ret_flags,
      time_rec, delegated_cred_handle);
  if (result != GSS_S_COMPLETE) {
    return 0;
  }
  gss_release_buffer(&minor_status, &output_token);
  gss_release_name(&minor_status, &src_name);
  gss_release_cred(&minor_status, &delegated_cred_handle);
  gss_delete_sec_context(&minor_status, &context_handle, GSS_C_NO_BUFFER);
  return 0;
}
```

The missing header is `gssapi/gssapi_ext.h`, which contains the definition of `gss_accept_sec_context_ext`.

The fix is to include this header with `extern "C" {}` to prevent name mangling, as the function is declared with C linkage in the header.