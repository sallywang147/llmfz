#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "gnutls/gnutls.h"

extern "C" {
#include "gnutls/gnutls.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string session_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 16));
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);
  gnutls_priority_set_direct(session, "NORMAL", nullptr);
  gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE,
                         gnutls_certificate_allocate_file("gnutls.crt"),
                         nullptr);
  gnutls_certificate_set_verify_flags(session, GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT);
  gnutls_dh_params_init(&session->dh_params);
  gnutls_dh_params_generate2(session->dh_params, 1024);
  gnutls_transport_set_ptr(session, reinterpret_cast<gnutls_transport_ptr_t>(0));
  int ret = gnutls_handshake(session);
  if (ret < 0) {
    // Handle handshake errors
    gnutls_deinit(session);
    return 0;
  }

  std::vector<uint8_t> input_buffer(stream.ConsumeIntegralInRange(0, 1024));
  stream.ConsumeBytes<uint8_t>(input_buffer.data(), input_buffer.size());

  struct mbuffer_st *out_buffer = nullptr;
  size_t bytes_received = gnutls_record_recv_data(session, &out_buffer);  // Corrected typo
  if (bytes_received > 0) {
    gnutls_record_recv_data(session, input_buffer.data(), input_buffer.size());
  }
  if (out_buffer != nullptr) {
    gnutls_free(out_buffer);
  }
  gnutls_deinit(session);
  return 0;
}