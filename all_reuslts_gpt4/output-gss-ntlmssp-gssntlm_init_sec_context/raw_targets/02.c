#include <string.h>

#include "gss_ntlmssp.h"
#include <gssapi.h>
#include <krb5.h>
#include <fuzzer/FuzzedDataProvider.h>

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);
  
  OM_uint32 maj_stat, min_stat;
  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gss_cred_id_t cred = GSS_C_NO_CREDENTIAL;
  gss_name_t target_name = GSS_C_NO_NAME;

  int req_flags = stream.ConsumeIntegral<int>();
  int time_req = stream.ConsumeIntegral<int>();

  gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;

  std::string token_str = stream.ConsumeRandomLengthString();
  input_token.length = token_str.size();
  input_token.value = (void*)token_str.c_str();

  maj_stat = gssntlm_init_sec_context(&min_stat, cred, &ctx, target_name, NULL, /* mech_type */
                                      req_flags, time_req, NULL, /* input_bindings */
                                      &input_token, NULL, /* actual_mech_type */
                                      &output_token, NULL, /* ret_flags */
                                      NULL); /* time_rec */

  gss_release_buffer(&min_stat, &output_token);

  gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);

  return 0;
}