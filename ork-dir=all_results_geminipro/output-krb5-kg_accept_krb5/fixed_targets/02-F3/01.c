#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "gssapi.h"
#include "krb5.h"

extern "C" {
#include "kgssapi_krb5.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();

  gss_ctx_id_t context_handle = GSS_C_NO_CONTEXT;
  gss_cred_id_t verifier_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;
  gss_channel_bindings_struct input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;
  gss_name_t src_name = GSS_C_NO_NAME;
  gss_OID_desc_struct mech_type = GSS_C_NO_OID;
  int ret_flags;
  int time_rec;
  gss_cred_id_t delegated_cred_handle = GSS_C_NO_CREDENTIAL;
  struct _krb5_gss_ctx_ext_rec exts;

  const int minor_status = stream.ConsumeIntegral<int>();
  const std::string text = stream.ConsumeRemainingBytesAsString();
  input_token.length = text.size();
  input_token.value = reinterpret_cast<uint8_t*>(const_cast<char*>(text.c_str()));

  kg_accept_krb5(&minor_status, &context_handle, verifier_cred_handle, &input_token,
                &input_chan_bindings, &src_name, &mech_type, &output_token,
                &ret_flags, &time_rec, &delegated_cred_handle, &exts);

  gss_release_buffer(&minor_status, &output_token);

  return 0;
}