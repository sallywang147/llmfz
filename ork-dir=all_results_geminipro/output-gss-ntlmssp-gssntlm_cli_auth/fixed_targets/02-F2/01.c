#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "gssntlm.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gssntlm_init();
    initialized = true;
  }

  int ret;
  struct gssntlm_ctx* ctx = gssntlm_ctx_alloc();
  if (ctx == nullptr) {
    return 0;
  }

  struct gssntlm_cred* cred = gssntlm_cred_alloc();
  if (cred == nullptr) {
    gssntlm_ctx_free(ctx);
    return 0;
  }

  struct ntlm_buffer target_info;
  target_info.length = 0;
  target_info.maximum_length = 0;
  target_info.buffer = nullptr;

  FuzzedDataProvider provider(data, size);
  ret = gssntlm_cli_auth(&provider.ConsumeIntegral<int>(), ctx, cred,
                         &target_info, provider.ConsumeIntegral<int>(),
                         nullptr);

  gssntlm_cred_free(cred);
  gssntlm_ctx_free(ctx);
  gssntlm_buffer_free(&target_info);

  return 0;
}