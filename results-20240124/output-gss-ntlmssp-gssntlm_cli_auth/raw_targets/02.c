 #include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "gssntlmssp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int minor_status;
  struct gssntlm_ctx* ctx = nullptr;
  struct gssntlm_cred* cred = nullptr;
  struct ntlm_buffer target_info;
  int in_flags = stream.ConsumeIntegral<int>();
  struct gss_channel_bindings_struct input_chan_bindings;

  gssntlm_init_ctx(&ctx);
  gssntlm_init_cred(&cred);

  target_info.length = stream.ConsumeIntegral<uint16_t>();
  target_info.maximum_length = stream.ConsumeIntegral<uint16_t>();
  target_info.buffer =
      static_cast<unsigned char*>(malloc(target_info.maximum_length));
  stream.ConsumeBytes<unsigned char>(target_info.buffer, target_info.length);

  gssntlm_cli_auth(&minor_status, ctx, cred, &target_info, in_flags,
                   &input_chan_bindings);

  gssntlm_free_ctx(&ctx);
  gssntlm_free_cred(&cred);
  free(target_info.buffer);

  return 0;
}