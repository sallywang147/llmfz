#include <string.h>

#include "gssapi.h"
#include "krb5.h"
#include "fuzzer/FuzzedDataProvider.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);
  
  OM_uint32 maj_stat, min_stat;
  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gss_name_t target_name = GSS_C_NO_NAME;
  gss_cred_id_t claimant_cred_handle = GSS_C_NO_CREDENTIAL;
  gss_OID_desc mech_type;
  gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;
  gss_OID_desc actual_mech_type;
  int req_flags = stream.ConsumeIntegral<int>();
  int time_req = stream.ConsumeIntegral<int>();
  int ret_flags = stream.ConsumeIntegral<int>();
  int time_rec = stream.ConsumeIntegral<int>();
  
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes());
  input_token.value = bytes.data();
  input_token.length = bytes.size();

  maj_stat = iakerb_gss_init_sec_context(&min_stat, claimant_cred_handle, &ctx, target_name, &mech_type, req_flags, time_req, NULL, &input_token, &actual_mech_type, &output_token, &ret_flags, &time_rec);

  gss_release_buffer(&min_stat, &output_token);
  gss_release_buffer(&min_stat, &input_token);

  if (GSS_ERROR(maj_stat)) {
    if (ctx != GSS_C_NO_CONTEXT)
      gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);
  }

  gss_release_name(&min_stat, &target_name);
  gss_release_cred(&min_stat, &claimant_cred_handle);

  return 0;
}