#include <string.h>

#include "gssapi.h"
#include "krb5.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  OM_uint32 maj_stat, min_stat;

  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gss_name_t target_name = GSS_C_NO_NAME;
  gss_cred_id_t claimant_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_OID_desc mech_type = {0, NULL};
  gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;
  krb5_gss_ctx_ext_rec exts = {0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

  if (Size < sizeof(input_token.length))
    return 0;

  input_token.length = *(unsigned short *)Data;

  Data += sizeof(input_token.length);
  Size -= sizeof(input_token.length);

  if (input_token.length == 0 || input_token.length > Size)
    return 0;

  input_token.value = malloc(input_token.length);
  memcpy(input_token.value, Data, input_token.length);

  maj_stat = krb5_gss_init_sec_context_ext(&min_stat, claimant_cred_handle, &ctx, target_name, &mech_type, 0, 0, NULL, &input_token, NULL, &output_token, NULL, NULL, &exts);

  gss_release_buffer(&min_stat, &output_token);
  gss_release_buffer(&min_stat, &input_token);

  if (GSS_ERROR(maj_stat)) {
    if (ctx != GSS_C_NO_CONTEXT)
      gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);
  }

  return 0;
}