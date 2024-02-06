#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <gnutls/gnutls.h>

extern "C" {
#include <gnutls/gnutls.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gnutls_session session;
  gnutls_init(&session, GNUTLS_CLIENT);
  gnutls_priority_set_direct(session, "NORMAL", NULL);

  const char* hostname = stream.ConsumeRandomLengthString(128).c_str();
  gnutls_server_name_t server_name;
  gnutls_server_name_init(&server_name);
  gnutls_server_name_set_hostname(&server_name, hostname);
  gnutls_session_set_server_name(session, &server_name);
  gnutls_server_name_deinit(&server_name);

  gnutls_transport_ptr transport;
  gnutls_transport_init(&transport);
  gnutls_transport_set_ptr(transport, (gnutls_transport_ptr_t) data, size);
  gnutls_transport_set_push_function(transport, [](gnutls_transport_ptr_t ptr,
                                                 const void* data, size_t size) {
    return size;
  });
  gnutls_transport_set_pull_function(transport, [](gnutls_transport_ptr_t ptr,
                                                 void* data, size_t size) {
    return 0;
  });
  gnutls_transport_set_close_function(transport, [](gnutls_transport_ptr_t ptr) {});
  gnutls_session_set_transport(session, transport);
  gnutls_transport_deinit(transport);

  gnutls_handshake_set_timeout(session, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);
  int init_value = stream.ConsumeBool() ? 1 : 0;
  int ret = gnutls_handshake(session);

  gnutls_deinit(session);
  return ret;
}