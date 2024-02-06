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

  FuzzedDataProvider stream(data, size);

  struct gnutls_session_int session;
  struct mbuffer_st *packet = nullptr;

  // Initialize session
  session.security_parameters.entity = GNUTLS_CLIENT;
  session.security_parameters.pversion = &gnutls_protocol_default;
  session.security_parameters.cs = &gnutls_cipher_null;
  session.security_parameters.kx_algorithm = GNUTLS_KX_RSA;
  session.security_parameters.mac = &gnutls_mac_null;
  session.security_parameters.compression_method = &gnutls_compression_null;
  session.security_parameters.cert_type = &gnutls_certificate_type_x509;
  session.security_parameters.server_precedence = 0;
  session.security_parameters.session_id_size = 0;
  session.security_parameters.session_id = nullptr;
  session.security_parameters.extensions = nullptr;
  session.security_parameters.priorities = nullptr;
  session.security_parameters.timestamp = 0;

  // Initialize packet
  packet = mbuffer_alloc((stream.remaining_bytes() > 0) ? stream.remaining_bytes() : 1, NULL);
  if (packet == nullptr) {
    return 0;
  }

  // Copy data to packet
  memcpy(_mbuffer_get_udata_ptr(packet), stream.ConsumeRemainingBytes().data(), packet->msg.size);

  // Call the target function
  gnutls_record_recv_packet(&session, &packet);

  // Clean up
  mbuffer_deinit(packet);

  return 0;
}