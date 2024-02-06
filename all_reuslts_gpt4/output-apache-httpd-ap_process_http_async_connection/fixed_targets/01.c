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

  struct conn_rec conn;
  conn.hostname = stream.ConsumeRandomLengthString().c_str();
  conn.remote_ip = stream.ConsumeRandomLengthString().c_str();
  conn.remote_host = stream.ConsumeRandomLengthString().c_str();
  conn.local_ip = stream.ConsumeRandomLengthString().c_str();
  conn.local_host = stream.ConsumeRandomLengthString().c_str();
  conn.remote_addr = NULL;
  conn.local_addr = NULL;
  conn.base_server = NULL;
  conn.master = NULL;
  conn.id = stream.ConsumeIntegral<long>();
  conn.keepalive = stream.ConsumeIntegral<int>();
  conn.keepalives = stream.ConsumeIntegral<int>();
  conn.log = NULL;
  conn.log_id = stream.ConsumeRandomLengthString().c_str();
  conn.input_filters = NULL;
  conn.output_filters = NULL;
  conn.sbh = NULL;
  conn.bucket_alloc = NULL;
  conn.current_thread = NULL;
  conn.csb = NULL;
  conn.data_in_input_filters = stream.ConsumeBool();
  conn.data_in_output_filters = stream.ConsumeBool();
  conn.aborted = stream.ConsumeBool();
  conn.connected = stream.ConsumeBool();
  conn.double_reverse = stream.ConsumeBool();
  conn.io_state = stream.ConsumeIntegral<int>();
  conn.io_state_set = stream.ConsumeBool();
  conn.current_filter = NULL;
  conn.input_data = NULL;
  conn.input_data_len = stream.ConsumeIntegral<int>();

  ap_process_http_async_connection(&conn);

  return 0;
}