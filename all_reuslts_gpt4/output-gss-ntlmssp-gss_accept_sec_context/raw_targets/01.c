#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "gss_ntlmssp.h"
#include <gssapi.h>
#include <krb5.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  OM_uint32 maj_stat, min_stat;
  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gss_name_t client_name = GSS_C_NO_NAME;
  gss_cred_id_t deleg_cred = GSS_C_NO_CREDENTIAL;

  do {
    unsigned short token_length;
    gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;

    if (size < sizeof(token_length))
      break;

    token_length = stream.ConsumeIntegral<unsigned short>();

    if (token_length == 0 || token_length > size)
      break;

    std::vector<uint8_t> token_data = stream.ConsumeBytes<uint8_t>(token_length);
    input_token.length = token_length;
    input_token.value = token_data.data();

    maj_stat = gss_accept_sec_context(&min_stat, &ctx, GSS_C_NO_CREDENTIAL,    /* server_creds */
                                      &input_token, GSS_C_NO_CHANNEL_BINDINGS, /* input_bindings */
                                      &client_name, NULL,                      /* mech_type */
                                      &output_token, NULL,                     /* ret_flags */
                                      NULL,                                    /* time */
                                      &deleg_cred);

    gss_release_buffer(&min_stat, &output_token);
  } while (maj_stat == GSS_S_CONTINUE_NEEDED);

  gss_release_name(&min_stat, &client_name);
  gss_release_cred(&min_stat, &deleg_cred);
  gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);

  return 0;
}