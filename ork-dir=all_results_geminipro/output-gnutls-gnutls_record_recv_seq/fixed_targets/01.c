#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <gnutls/gnutls.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);
  gnutls_priority_set_direct(&session, "PERFORMANCE", NULL);

  const std::string data_to_send = stream.ConsumeRemainingBytesAsString();
  const char* data_to_send_ptr = data_to_send.c_str();
  const size_t data_to_send_size = data_to_send.size();

  size_t bytes_received = gnutls_record_recv(&session,
                                                 const_cast<char*>(data_to_send_ptr),
                                                 data_to_send_size, NULL);
  if (bytes_received > 0) {
    gnutls_record_recv_seq(&session, NULL, 0, NULL);  // Fix: Call gnutls_record_recv_seq
  }

  gnutls_deinit(&session);
  return 0;
}