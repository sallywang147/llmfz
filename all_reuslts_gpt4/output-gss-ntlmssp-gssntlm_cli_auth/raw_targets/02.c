#include <fuzzer/FuzzedDataProvider.h>
#include "gss_ntlmssp.h"
#include <gssapi.h>
#include <krb5.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int minor_status = 0;
  struct gssntlm_ctx ctx = {0};
  struct gssntlm_cred cred = {0};
  struct ntlm_buffer target_info = {0};
  int in_flags = stream.ConsumeIntegral<int>();
  struct gss_channel_bindings_struct input_chan_bindings = {0};

  // Consume data for target_info
  size_t target_info_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  target_info.length = target_info_size;
  target_info.data = (uint8_t *)malloc(target_info_size);
  if (target_info.data == NULL) {
    return 0;
  }
  memcpy(target_info.data, stream.ConsumeBytes<uint8_t>(target_info_size).data(), target_info_size);

  // Call the function to be fuzzed
  gssntlm_cli_auth(&minor_status, &ctx, &cred, &target_info, in_flags, &input_chan_bindings);

  // Cleanup
  free(target_info.data);

  return 0;
}