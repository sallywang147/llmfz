#include "h2o.h"
#include "h2o/http1.h"

extern "C" {
#include "h2o/http2.h"
}

#define HTTP1

#include "h2o/http1.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  h2o_accept_ctx_t *ctx = h2o_accept_ctx_create();
  h2o_socket_t *sock = h2o_socket_create(0, H2O_SOCKET_FLAG_TCP);
  h2o_accept(ctx, sock);
  h2o_socket_close(sock);
  h2o_accept_ctx_destroy(ctx);
  return 0;
}