#include <string.h>

#include "gssapi.h"
#include "krb5.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);
  OM_uint32 maj_stat, min_stat;
  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gss_name_t client_name = GSS_C_NO_NAME;
  gss_cred_id_t deleg_cred = GSS_C_NO_CREDENTIAL;
  gss_OID_desc_struct* actual_mech_type = nullptr;
  gss_buffer_desc_struct output_token = GSS_C_EMPTY_BUFFER;
  int ret_flags = 0;
  int time_rec = 0;

  unsigned short token_length;
  gss_buffer_desc input_token;

  if (Size < sizeof(token_length))
    return 0;

  token_length = stream.ConsumeIntegral<unsigned short>();

  if (token_length == 0 || token_length > Size)
    return 0;

  input_token.length = token_length;
  input_token.value = malloc(token_length);
  memcpy(input_token.value, Data, token_length);

  maj_stat = krb5_gss_init_sec_context(&min_stat, deleg_cred, &ctx, client_name, nullptr, 0, 0, nullptr, &input_token, &actual_mech_type, &output_token, &ret_flags, &time_rec);

  gss_release_buffer(&min_stat, &output_token);
  gss_release_buffer(&min_stat, &input_token);

  if (GSS_ERROR(maj_stat)) {
    if (ctx != GSS_C_NO_CONTEXT)
      gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);
  }

  gss_release_name(&min_stat, &client_name);
  gss_release_cred(&min_stat, &deleg_cred);

  return 0;
}