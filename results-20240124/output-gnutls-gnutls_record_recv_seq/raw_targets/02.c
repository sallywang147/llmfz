 #include <stdint.h>
#include <stdlib.h>

#include <gnutls/gnutls.h>
#include <gnutls/record.h>

#include "fuzzer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  gnutls_session_int session = {0};
  gnutls_record_recv_seq(&session, nullptr, 0, nullptr);

  return 0;
}