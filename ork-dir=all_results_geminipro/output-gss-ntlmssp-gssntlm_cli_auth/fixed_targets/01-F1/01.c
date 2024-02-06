#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <gssapi.h>
#include <krb5.h>
#include <ntlmssp.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  OM_uint32 maj_stat, min_stat;
  gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
  gssntlm_cred cred = {0};
  struct ntlm_buffer target_info = {0};
  gss_channel_bindings_struct input_chan_bindings = {0};
  int in_flags = 0;
  int minor_status = 0;

  // Parse the fuzzed data.
  FuzzedDataProvider data_provider(Data, Size);
  std::vector<uint8_t> target_info_data =
      data_provider.ConsumeBytes<uint8_t>(data_provider.remaining_bytes());
  target_info.length = target_info_data.size();
  target_info.data = target_info_data.data();

  // Call the function to be fuzzed.
  maj_stat = gssntlm_cli_auth(&minor_status, &ctx, &cred, &target_info, in_flags,
                              &input_chan_bindings);

  // Clean up.
  gss_release_cred(&min_stat, &cred.gss_cred);
  free(target_info.data);

  return 0;
}