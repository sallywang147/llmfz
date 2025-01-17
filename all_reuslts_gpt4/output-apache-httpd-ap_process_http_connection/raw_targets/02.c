#include <fuzzer/FuzzedDataProvider.h>
#include "httpd.h"
#include "http_core.h"
#include "http_connection.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct conn_rec c;
  c.base_server = NULL;
  c.conn_config = NULL;
  c.notes = NULL;
  c.input_filters = NULL;
  c.output_filters = NULL;
  c.sbh = NULL;
  c.bucket_alloc = NULL;
  c.current_thread = NULL;
  c.master = NULL;
  c.id = stream.ConsumeIntegral<long>();
  c.log = NULL;
  c.log_id = NULL;
  c.local_ip = stream.ConsumeRandomLengthString().c_str();
  c.local_host = stream.ConsumeRandomLengthString().c_str();
  c.remote_ip = stream.ConsumeRandomLengthString().c_str();
  c.remote_host = stream.ConsumeRandomLengthString().c_str();
  c.remote_logname = stream.ConsumeRandomLengthString().c_str();
  c.aborted = stream.ConsumeBool();
  c.keepalive = stream.ConsumeEnum<ap_conn_keepalive_e>();
  c.double_reverse = stream.ConsumeBool();
  c.keepalives = stream.ConsumeIntegral<int>();
  c.local_addr = NULL;
  c.remote_addr = NULL;
  c.data_in_input_filters = stream.ConsumeBool();
  c.data_in_output_filters = stream.ConsumeBool();
  c.ignore_eos = stream.ConsumeBool();

  ap_process_http_connection(&c);

  return 0;
}