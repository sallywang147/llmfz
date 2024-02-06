#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "httpd.h"
#include "http_core.h"
#include "http_connection.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Apache
  static int initialized = 0;
  if (!initialized) {
    apr_initialize();
    atexit(apr_terminate);
    initialized = 1;
  }

  // Create a pool
  apr_pool_t* p = NULL;
  if (apr_pool_create(&p, NULL) != APR_SUCCESS) {
    return 0;
  }

  // Create a connection record
  conn_rec* c = (conn_rec*)apr_pcalloc(p, sizeof(conn_rec));
  if (!c) {
    apr_pool_destroy(p);
    return 0;
  }

  // Initialize the connection record
  c->pool = p;
  c->base_server = (server_rec*)apr_pcalloc(p, sizeof(server_rec));
  c->bucket_alloc = apr_bucket_alloc_create(p);
  c->current_thread = apr_os_thread_current();

  // Process the connection
  ap_process_http_sync_connection(c);

  // Clean up
  apr_pool_destroy(p);

  return 0;
}