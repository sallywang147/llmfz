#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cmp.h"
#include "cmp_ctx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ossl_cmp_ctx_st *client_ctx = OSSL_CMP_CTX_new();
  if (client_ctx == nullptr) {
    return 0;
  }

  struct ossl_cmp_msg_st *req = OSSL_CMP_MSG_new();
  if (req == nullptr) {
    OSSL_CMP_CTX_free(client_ctx);
    return 0;
  }

  // Consume some data to fill the request
  size_t req_data_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
  std::vector<uint8_t> req_data = stream.ConsumeBytes<uint8_t>(req_data_size);
  req->bodyvalue = req_data.data();

  // Perform the server operation
  struct ossl_cmp_msg_st *res = OSSL_CMP_CTX_server_perform(client_ctx, req);

  // Cleanup
  OSSL_CMP_MSG_free(req);
  OSSL_CMP_CTX_free(client_ctx);

  return 0;
}