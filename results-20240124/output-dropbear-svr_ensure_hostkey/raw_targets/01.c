 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dropbear.h"
#include "dropbear_types.h"
#include "dropbear_hostkey.h"
#include "dropbear_keyfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  dropbear_context dropbear_ctx;
  dropbear_ctx.hostkey = nullptr;
  dropbear_ctx.rsa_key = nullptr;
  dropbear_ctx.dss_key = nullptr;
  dropbear_ctx.ecdh_key = nullptr;
  dropbear_ctx.ed25519_key = nullptr;

  svr_ensure_hostkey(&dropbear_ctx);
  dropbear_free(dropbear_ctx.hostkey);
  return 0;
}