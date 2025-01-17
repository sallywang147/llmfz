#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Apache server
  static bool initialized = false;
  if (!initialized) {
    ap_open_stderr_log();
    ap_server_conf = ap_read_config();
    initialized = true;
  }

  // Create a connection record
  conn_rec* c = (conn_rec*) apr_pcalloc(ap_server_conf->pool, sizeof(conn_rec));
  if (!c) {
    return 0;
  }

  // Populate the connection record with fuzzed data
  c->local_ip = stream.ConsumeRandomLengthString().c_str();
  c->remote_ip = stream.ConsumeRandomLengthString().c_str();
  c->remote_host = stream.ConsumeRandomLengthString().c_str();
  c->remote_logname = stream.ConsumeRandomLengthString().c_str();
  c->local_host = stream.ConsumeRandomLengthString().c_str();
  c->aborted = stream.ConsumeBool();
  c->keepalive = stream.ConsumeBool();
  c->double_reverse = stream.ConsumeBool();
  c->keepalives = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  ap_process_http_sync_connection(c);

  return 0;
}