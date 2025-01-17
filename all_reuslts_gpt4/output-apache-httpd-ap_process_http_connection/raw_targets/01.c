#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "httpd.h"
#include "http_core.h"
#include "http_config.h"
#include "http_protocol.h"
#include "http_request.h"
#include "ap_config.h"
#include "apr_strings.h"
#include "apr_network_io.h"
#include "apr_poll.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize Apache's server_rec with default values
  server_rec *s = ap_server_conf;
  conn_rec *c = (conn_rec *)apr_pcalloc(s->process->pool, sizeof(conn_rec));

  // Initialize connection record
  c->pool = s->process->pool;
  c->base_server = s;
  c->bucket_alloc = apr_bucket_alloc_create(c->pool);
  c->current_thread = thd;
  c->conn_config = ap_create_conn_config(c->pool);
  c->notes = apr_table_make(c->pool, 5);
  c->input_filters = c->output_filters = NULL;
  c->data_in_input_filters = c->data_in_output_filters = 0;
  c->input_filter_handle = c->output_filter_handle = NULL;

  // Initialize remaining conn_rec fields with fuzzed data
  c->id = stream.ConsumeIntegral<long>();
  c->conn_state = (conn_state_t) stream.ConsumeIntegral<int>();
  c->sbh = (void *) stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, 10)).data();
  c->data = (void *) stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, 10)).data();
  c->clogging_input_filters = stream.ConsumeBool();
  c->cs = (conn_state_t *) stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, 10)).data();
  c->log = (void *) stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, 10)).data();
  c->log_id = (char *) stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 10)).c_str();
  c->log_id_len = stream.ConsumeIntegral<size_t>();
  c->keepalives = stream.ConsumeIntegral<int>();
  c->local_ip = (char *) stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 10)).c_str();
  c->local_host = (char *) stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 10)).c_str();

  // Call the function to be fuzzed
  ap_process_http_connection(c);

  return 0;
}