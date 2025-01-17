#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  gnutls_session_t session;
  int ret = gnutls_init(&session, GNUTLS_SERVER);
  if (ret != GNUTLS_E_SUCCESS) {
    return 0;
  }

  gnutls_datum_t datum;
  datum.data = stream.ConsumeRemainingBytes<uint8_t>().data();
  datum.size = size;

  ret = gnutls_record_recv_packet(session, &datum);
  if (ret < 0) {
    gnutls_deinit(session);
    return 0;
  }

  gnutls_deinit(session);

  return 0;
}