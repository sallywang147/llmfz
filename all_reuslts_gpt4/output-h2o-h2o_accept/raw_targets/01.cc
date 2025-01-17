#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "h2o/socket.h"
#include "h2o.h"

struct st_h2o_accept_ctx_t {
  h2o_context_t *ctx;
  h2o_hostconf_t **hosts;
  h2o_access_log_filehandle_t *logfh;
  struct {
    h2o_iovec_t host;
    h2o_iovec_t realm;
    h2o_iovec_t _unused;
  } ssl_setup_errors;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize h2o_accept_ctx_t
  h2o_context_t ctx;
  h2o_hostconf_t *hosts = NULL;
  h2o_access_log_filehandle_t logfh;
  st_h2o_accept_ctx_t accept_ctx = {&ctx, &hosts, &logfh, {h2o_iovec_init(NULL, 0), h2o_iovec_init(NULL, 0), h2o_iovec_init(NULL, 0)}};

  // Initialize h2o_socket_t
  h2o_socket_t sock;

  // Call the target function
  h2o_accept(&accept_ctx, &sock);

  return 0;
}