#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gnutls/gnutls.h"
#include "gnutls/mbuffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  struct gnutls_session_int session;
  struct mbuffer_st* mbuffer = nullptr;
  
  FuzzedDataProvider provider(data, size);

  // Extract the data for the session and mbuffer from the fuzzing input
  if (provider.remaining_bytes() > sizeof(session)) {
    provider.ConsumeData(&session, sizeof(session));
  } else {
    return 0;
  }

  // Call the function to be fuzzed
  gnutls_record_recv_packet(&session, &mbuffer);

  gnutls_global_deinit();

  return 0;
}