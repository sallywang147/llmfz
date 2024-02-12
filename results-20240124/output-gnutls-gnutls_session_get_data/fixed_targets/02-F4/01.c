#include <stddef.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "fuzzer.h"
#include "gnutls/gnutls.h"

extern "C" {
#include <alloca.h>
#include <stdckdint.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);
  gnutls_priority_set_direct(session, "NORMAL", NULL);

  FuzzedDataProvider provider(data, size);
  const size_t max_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> buffer(max_size);
  size_t written;
  gnutls_session_get_data(session, reinterpret_cast<char*>(buffer.data()),
                          &written);
  return 0;
}