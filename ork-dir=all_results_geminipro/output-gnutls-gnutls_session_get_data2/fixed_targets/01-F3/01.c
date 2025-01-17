#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <gnutls/gnutls.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t session_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t datum_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct gnutls_session_int* session =
      static_cast<gnutls_session_int*>(std::malloc(session_size));
  memset(session, 0, session_size);
  struct gnutls_datum_t datum;
  memset(&datum, 0, sizeof(datum));
  datum.data = std::malloc(datum_size);
  memset(datum.data, 0, datum_size);
  datum.size = datum_size;
  int ret = gnutls_session_get_data2(session, &datum);
  gnutls_deinit(session);  // Properly clean up the gnutls session
  std::free(session);
  std::free(datum.data);
  return ret;
}