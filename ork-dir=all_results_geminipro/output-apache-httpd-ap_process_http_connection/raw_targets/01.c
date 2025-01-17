#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "apr_strings.h"
#include "apr_tables.h"
#include "ap_config.h"
#include "ap_mmn.h"
#include "ap_mpm.h"
#include "ap_regex.h"
#include "http_config.h"
#include "http_connection.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_vhost.h"
#include "mod_core.h"
#include "scoreboard.h"

/*
 * This is a fuzzer for the Apache HTTP Server.
 *
 * It works by creating a fake connection structure and then calling
 * ap_process_http_connection() on it. The fake connection structure is
 * populated with data from the fuzzer's input buffer.
 *
 * The fuzzer will try to exercise all of the different code paths in
 * ap_process_http_connection(). This is done by sending a variety of
 * different HTTP requests to the fuzzer. The fuzzer will also try to send
 * invalid HTTP requests to the fuzzer. This is done to try to find bugs in
 * the Apache HTTP Server.
 */

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Create a fake connection structure.
  struct conn_rec* c = (struct conn_rec*)calloc(1, sizeof(struct conn_rec));
  if (c == nullptr) {
    return 0;
  }

  // Populate the fake connection structure with data from the fuzzer's input buffer.
  FuzzedDataProvider stream(data, size);
  c->client_socket = stream.ConsumeIntegral<int>();
  c->local_addr = stream.ConsumeIntegral<int>();
  c->remote_addr = stream.ConsumeIntegral<int>();
  c->local_port = stream.ConsumeIntegral<int>();
  c->remote_port = stream.ConsumeIntegral<int>();
  c->sbh = stream.ConsumeIntegral<int>();
  c->cs = stream.ConsumeIntegral<int>();
  c->id = stream.ConsumeIntegral<int>();
  c->keepalive = stream.ConsumeIntegral<int>();
  c->state = stream.ConsumeIntegral<int>();
  c->data = stream.ConsumeIntegral<int>();
  c->bucket_alloc = stream.ConsumeIntegral<int>();
  c->bucket = stream.ConsumeIntegral<int>();
  c->pool = stream.ConsumeIntegral<int>();

  // Create a fake request structure.
  struct request_rec* r = (struct request_rec*)calloc(1, sizeof(struct request_rec));
  if (r == nullptr) {
    free(c);
    return 0;
  }

  // Populate the fake request structure with data from the fuzzer's input buffer.
  r->connection = c;
  r->server = stream.ConsumeIntegral<int>();
  r->pool = stream.ConsumeIntegral<int>();
  r->request_config = stream.ConsumeIntegral<int>();
  r->parsed_uri = stream.ConsumeIntegral<int>();
  r->hostname = stream.ConsumeIntegral<int>();
  r->method = stream.ConsumeIntegral<int>();
  r->protocol = stream.ConsumeIntegral<int>();
  r->assbackwards = stream.ConsumeIntegral<int>();
  r->setup_done = stream.ConsumeIntegral<int>();
  r->header_only = stream.ConsumeIntegral<int>();
  r->chunked = stream.ConsumeIntegral<int>();
  r->expecting_100 = stream.ConsumeIntegral<int>();
  r->status = stream.ConsumeIntegral<int>();
  r->status_line = stream.ConsumeIntegral<int>();
  r->proto_num = stream.ConsumeIntegral<int>();
  r->headers_in = stream.ConsumeIntegral<int>();
  r->headers_out = stream.ConsumeIntegral<int>();
  r->err_headers_out = stream.ConsumeIntegral<int>();
  r->subprocess_env = stream.ConsumeIntegral<int>();
  r->headers = stream.ConsumeIntegral<int>();
  r->subprocess_env = stream.ConsumeIntegral<int>();
  r->sent_bodyct = stream.ConsumeIntegral<int>();
  r->bytes_sent = stream.ConsumeIntegral<int>();
  r->bytes_sent_out = stream.ConsumeIntegral<int>();
  r->bytes_read = stream.ConsumeIntegral<int>();
  r->read_length = stream.ConsumeIntegral<int>();
  r->read_pos = stream.ConsumeIntegral<int>();
  r->remaining = stream.ConsumeIntegral<int>();
  r->memlen = stream.ConsumeIntegral<int>();
  r->pos = stream.ConsumeIntegral<int>();
  r->handler = stream.ConsumeIntegral<int>();
  r->output_filters = stream.ConsumeIntegral<int>();
  r->input_filters = stream.ConsumeIntegral<int>();
  r->finfo = stream.ConsumeIntegral<int>();
  r->main = stream.ConsumeIntegral<int>();
  r->prev = stream.ConsumeIntegral<int>();
  r->next = stream.ConsumeIntegral<int>();

  // Call ap_process_http_connection() on the fake connection structure.
  ap_process_http_connection(c);

  // Free the fake connection structure and the fake request structure.
  free(c);
  free(r);

  return 0;
}