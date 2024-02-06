#include <fuzzer/FuzzedDataProvider.h>
#include "gss_ntlmssp.h"
#include <gssapi.h>
#include <krb5.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int minor_status = 0;
  struct gssntlm_ctx ctx;
  struct gssntlm_cred cred;
  struct ntlm_buffer target_info;
  struct gss_channel_bindings_struct input_chan_bindings;

  // Initialize the structures
  memset(&ctx, 0, sizeof(ctx));
  memset(&cred, 0, sizeof(cred));
  memset(&target_info, 0, sizeof(target_info));
  memset(&input_chan_bindings, 0, sizeof(input_chan_bindings));

  // Fill the structures with fuzzing data
  target_info.length = stream.ConsumeIntegralInRange<uint32_t>(0, 1024);
  target_info.data = (uint8_t *)malloc(target_info.length);
  if (target_info.data == NULL) {
    return 0;
  }
  memcpy(target_info.data, stream.ConsumeRemainingBytes().data(), target_info.length);

  int in_flags = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  gssntlm_cli_auth(&minor_status, &ctx, &cred, &target_info, in_flags, &input_chan_bindings);

  // Cleanup
  free(target_info.data);

  return 0;
}