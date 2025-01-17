#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gnutls_session_t session = nullptr;
  gnutls_init(&session, GNUTLS_CLIENT);

  const size_t session_data_size = stream.ConsumeIntegral<size_t>();
  char* session_data = new char[session_data_size];
  stream.ConsumeBytes(session_data, session_data_size);
  int ret = gnutls_session_set_data(session, session_data, session_data_size);
  if (ret != GNUTLS_E_SUCCESS) {
    gnutls_deinit(session);
    delete[] session_data;
    return 0;
  }

  size_t actual_session_data_size = 0;
  char* actual_session_data = nullptr;
  ret = gnutls_session_get_data(session, actual_session_data, &actual_session_data_size);
  if (ret != GNUTLS_E_SUCCESS) {
    gnutls_deinit(session);
    delete[] session_data;
    return 0;
  }

  gnutls_deinit(session);
  delete[] session_data;
  delete[] actual_session_data;
  return 0;
}