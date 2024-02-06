#include <fuzzer/FuzzedDataProvider.h>
#include "gnutls_int.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct gnutls_session_int session;
  int ms = stream.ConsumeIntegral<int>();

  check_session_status(&session, ms);

  return 0;
}