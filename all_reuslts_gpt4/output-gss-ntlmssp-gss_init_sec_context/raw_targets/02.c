#include <fuzzer/FuzzedDataProvider.h>
#include "gss_ntlmssp.h"
#include <gssapi.h>
#include <krb5.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  OM_uint32 min_stat;
  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gss_name_t target_name = GSS_C_NO_NAME;
  gss_cred_id_t cred_handle = GSS_C_NO_CREDENTIAL;
  gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;
  gss_OID_desc mech_type;
  gss_OID_desc *actual_mech_type;
  int req_flags = stream.ConsumeIntegral<int>();
  int time_req = stream.ConsumeIntegral<int>();
  int ret_flags;

  // Consume bytes for input_token
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2);
  input_token.length = bytes.size();
  input_token.value = bytes.data();

  // Consume bytes for mech_type
  std::vector<uint8_t> bytes2 = stream.ConsumeRemainingBytes<uint8_t>();
  mech_type.length = bytes2.size();
  mech_type.elements = bytes2.data();

  gss_init_sec_context(&min_stat, cred_handle, &ctx, target_name, &mech_type, req_flags, time_req, NULL, &input_token, &actual_mech_type, &output_token, &ret_flags, NULL);

  gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);

  return 0;
}