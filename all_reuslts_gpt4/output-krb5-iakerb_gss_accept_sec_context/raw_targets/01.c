#include <string.h>
#include "gssapi.h"
#include "krb5.h"
#include "fuzzer/FuzzedDataProvider.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  OM_uint32 maj_stat, min_stat;

  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gss_name_t client_name = GSS_C_NO_NAME;
  gss_cred_id_t deleg_cred = GSS_C_NO_CREDENTIAL;

  /* Each fuzz input contains multiple tokens preceded by a length field.
   * Process them in turn with iakerb_gss_accept_sec_context while
   * GSS_S_CONTINUE_NEEDED is set
   */
  do {
    unsigned short token_length;

    gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;

    if (!stream.remaining_bytes())
      break;

    token_length = stream.ConsumeIntegral<unsigned short>();

    if (token_length == 0 || token_length > stream.remaining_bytes())
      break;

    input_token.length = token_length;
    input_token.value = malloc(token_length);
    memcpy(input_token.value, stream.ConsumeBytes(token_length).data(), token_length);

    maj_stat = iakerb_gss_accept_sec_context(&min_stat, &ctx, GSS_C_NO_CREDENTIAL,    /* server_creds */
                                             &input_token, GSS_C_NO_CHANNEL_BINDINGS, /* input_bindings */
                                             &client_name, NULL,                      /* mech_type */
                                             &output_token, NULL,                     /* ret_flags */
                                             NULL,                                    /* time */
                                             &deleg_cred);

    gss_release_buffer(&min_stat, &output_token);
    gss_release_buffer(&min_stat, &input_token);

    if (GSS_ERROR(maj_stat)) {
      if (ctx != GSS_C_NO_CONTEXT)
        gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);
      break;
    }
  } while (maj_stat & GSS_S_CONTINUE_NEEDED);

  gss_release_name(&min_stat, &client_name);
  gss_release_cred(&min_stat, &deleg_cred);

  return 0;
}