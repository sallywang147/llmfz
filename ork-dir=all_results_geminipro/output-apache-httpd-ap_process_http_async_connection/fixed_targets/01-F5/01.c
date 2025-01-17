#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ap_config.h"
#include "ap_mmn.h"
#include "ap_mpm.h"
#include "ap_regex.h"
#include "http_config.h"
#include "http_connection.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_vhost.h"
#include "util_filter.h"

extern "C" {
#include "apr_network_io.h"
#include "apr_strings.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  request_rec* request = (request_rec*)calloc(1, sizeof(request_rec));
  request->pool = ap_make_sub_pool(nullptr);
  request->hostname = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  request->connection = (conn_rec*)calloc(1, sizeof(conn_rec));
  request->connection->local_addr = (sockaddr*)calloc(1, sizeof(sockaddr));
  request->connection->local_addr->sa_family = AF_INET;
  request->connection->local_addr->sa_data[0] = 0x02;
  request->connection->local_addr->sa_data[1] = 0x00;
  request->connection->local_addr->sa_data[2] = 0x00;
  request->connection->local_addr->sa_data[3] = 0x00;
  request->connection->local_addr->sa_data[4] = 0x00;
  request->connection->local_addr->sa_data[5] = 0x00;
  request->connection->local_addr->sa_data[6] = 0x00;
  request->connection->local_addr->sa_data[7] = 0x00;
  request->connection->local_addr->sa_data[8] = 0x00;
  request->connection->local_addr->sa_data[9] = 0x00;
  request->connection->local_addr->sa_data[10] = 0x00;
  request->connection->local_addr->sa_data[11] = 0x00;
  request->connection->local_addr->sa_data[12] = 0x00;
  request->connection->local_addr->sa_data[13] = 0x00;
  request->connection->local_addr->sa_data[14] = 0x00;
  request->connection->local_addr->sa_data[15] = 0x01;
  request->connection->local_port = stream.ConsumeIntegralInRange(0, 65535);
  request->connection->remote_addr = (sockaddr*)calloc(1, sizeof(sockaddr));
  request->connection->remote_addr->sa_family = AF_INET;
  request->connection->remote_addr->sa_data[0] = 0x02;
  request->connection->remote_addr->sa_data[1] = 0x00;
  request->connection->remote_addr->sa_data[2] = 0x00;
  request->connection->remote_addr->sa_data[3] = 0x00;
  request->connection->remote_addr->sa_data[4] = 0x00;
  request->connection->remote_addr->sa_data[5] = 0x00;
  request->connection->remote_addr->sa_data[6] = 0x00;
  request->connection->remote_addr->sa_data[7] = 0x00;
  request->connection->remote_addr->sa_data[8] = 0x00;
  request->connection->remote_addr->sa_data[9] = 0x00;
  request->connection->remote_addr->sa_data[10] = 0x00;
  request->connection->remote_addr->sa_data[11] = 0x00;
  request->connection->remote_addr->sa_data[12] = 0x00;
  request->connection->remote_addr->sa_data[13] = 0x00;
  request->connection->remote_addr->sa_data[14] = 0x00;
  request->connection->remote_addr->sa_data[15] = 0x02;
  request->connection->remote_port = stream.ConsumeIntegralInRange(0, 65535);

  int ret = ap_process_http_async_connection(request->connection);
  ap_destroy_sub_pool(request->pool);
  free(request->connection->local_addr);
  free(request->connection->remote_addr);
  free(request->connection);
  free(request);
  return ret;
}