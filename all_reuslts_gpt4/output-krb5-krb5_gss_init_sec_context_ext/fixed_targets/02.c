#include <string.h>
#include "gssapi.h"
#include "krb5.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  OM_uint32 min_stat;
  gss_cred_id_t cred_handle = GSS_C_NO_CREDENTIAL;
  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gss_name_t target_name = GSS_C_NO_NAME;
  gss_OID_desc mech_type;
  int req_flags = stream.ConsumeIntegral<int>();
  int time_req = stream.ConsumeIntegral<int>();
  gss_channel_bindings_t input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;
  gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;
  gss_OID_desc *actual_mech_type = NULL;
  int ret_flags;
  int time_rec;
  struct _krb5_gss_ctx_ext_rec exts;

  size_t token_length = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> token_bytes = stream.ConsumeBytes<uint8_t>(token_length);
  input_token.length = token_length;
  input_token.value = token_bytes.data();

  mech_type.length = stream.ConsumeIntegralInRange<OM_uint32>(0, size);
  std::vector<uint8_t> mech_bytes = stream.ConsumeBytes<uint8_t>(mech_type.length);
  mech_type.elements = mech_bytes.data();

  krb5_gss_init_sec_context_ext(&min_stat, cred_handle, &ctx, target_name, &mech_type, req_flags, time_req, input_chan_bindings, &input_token, &actual_mech_type, &output_token, &ret_flags, &time_rec, &exts);

  gss_release_buffer(&min_stat, &output_token);
  gss_release_buffer(&min_stat, &input_token);

  return 0;
}