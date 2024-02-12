#include <stddef.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "h2o.h"
#include "h2o/h2o.h"
#include "h2o/memory.h"
#include "h2o/string_.h"
#include "h2o/http2.h"
#include "h2o/http2_common.h"
#include "h2o/http2_frame.h"
#include "h2o/http2_transport.h"
#include "h2o/http2_stream.h"
#include "h2o/http2_conn_pool.h"
#include "h2o/http2_server.h"
#include "h2o/http2_client.h"
#include "h2o/http1.h"
#include "h2o/http1_server.h"
#include "h2o/http1_client.h"
#include "h2o/websocket.h"
#include "h2o/serverutil.h"
#include "h2o/http2_configurator.h"
#include "h2o/url.h"
#include "h2o/memcached.h"

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct st_ptls_compressed_certificate_entry_t entry;
  memset(&entry, 0, sizeof(entry));
  entry.type = stream.ConsumeIntegral<uint8_t>();
  entry.certificate_list_size = stream.ConsumeIntegral<uint32_t>();
  entry.certificate_list = (struct st_ptls_certificate_entry_t*)malloc(sizeof(struct st_ptls_certificate_entry_t) * entry.certificate_list_size);
  for (uint32_t i = 0; i < entry.certificate_list_size; ++i) {
    entry.certificate_list[i].certificate_size = stream.ConsumeIntegral<uint32_t>();
    entry.certificate_list[i].certificate = (uint8_t*)malloc(entry.certificate_list[i].certificate_size);
    stream.ConsumeBytes<uint8_t>(entry.certificate_list[i].certificate, entry.certificate_list[i].certificate_size);
  }
  entry.ocsp_status_list_size = stream.ConsumeIntegral<uint32_t>();
  entry.ocsp_status_list = (struct st_ptls_ocsp_status_entry_t*)malloc(sizeof(struct st_ptls_ocsp_status_entry_t) * entry.ocsp_status_list_size);
  for (uint32_t i = 0; i < entry.ocsp_status_list_size; ++i) {
    entry.ocsp_status_list[i].ocsp_status_size = stream.ConsumeIntegral<uint32_t>();
    entry.ocsp_status_list[i].ocsp_status = (uint8_t*)malloc(entry.ocsp_status_list[i].ocsp_status_size);
    stream.ConsumeBytes<uint8_t>(entry.ocsp_status_list[i].ocsp_status, entry.ocsp_status_list[i].ocsp_status_size);
  }
  entry.scts_list_size = stream.ConsumeIntegral<uint32_t>();
  entry.scts_list = (struct st_ptls_sct_entry_t*)malloc(sizeof(struct st_ptls_sct_entry_t) * entry.scts_list_size);
  for (uint32_t i = 0; i < entry.scts_list_size; ++i) {
    entry.scts_list[i].sct_size = stream.ConsumeIntegral<uint32_t>();
    entry.scts_list[i].sct = (uint8_t*)malloc(entry.scts_list[i].sct_size);
    stream.ConsumeBytes<uint8_t>(entry.scts_list[i].sct, entry.scts_list[i].sct_size);
  }

  struct st_h2o_iovec_t iov;
  h2o_iovec_init(&iov, NULL, 0);
  char ocsp_status[1024];
  build_compressed(&entry, &iov, 1024, ocsp_status, sizeof(ocsp_status));

  h2o_iovec_destroy(&iov);

  for (uint32_t i = 0; i < entry.certificate_list_size; ++i) {
    free(entry.certificate_list[i].certificate);
  }
  free(entry.certificate_list);
  for (uint32_t i = 0; i < entry.ocsp_status_list_size; ++i) {
    free(entry.ocsp_status_list[i].ocsp_status);
  }
  free(entry.ocsp_status_list);
  for (uint32_t i = 0; i < entry.scts_list_size; ++i) {
    free(entry.scts_list[i].sct);
  }
  free(entry.scts_list);

  return 0;
}