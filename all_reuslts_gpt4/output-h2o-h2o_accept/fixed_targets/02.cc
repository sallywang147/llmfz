#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "h2o.h"
#include "h2o/socket.h"
#include "h2o/serverutil.h"

struct st_h2o_accept_ctx_t {
  h2o_context_t *ctx;
  h2o_hostconf_t **hosts;
  h2o_access_log_filehandle_t *logconf;
  h2o_socket_t *sock;
};

struct st_h2o_socket_t {
  h2o_socket_t *sock;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the h2o context
  h2o_context_t ctx;
  h2o_context_init(&ctx, h2o_evloop_create(), &config);

  // Initialize the accept context
  struct st_h2o_accept_ctx_t accept_ctx;
  accept_ctx.ctx = &ctx;
  accept_ctx.hosts = config.hosts;
  accept_ctx.logconf = NULL;
  accept_ctx.sock = NULL;

  // Initialize the socket
  struct st_h2o_socket_t sock;
  sock.sock = NULL;

  // Call the target function
  h2o_accept(&accept_ctx, &sock);

  return 0;
}