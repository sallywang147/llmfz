#include <fuzzer/FuzzedDataProvider.h>
#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize GnuTLS
  gnutls_global_init();

  // Create a GnuTLS session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  // We need to provide a function for GnuTLS to read data from. We'll use a lambda function for that.
  gnutls_transport_set_push_function(session, [](gnutls_transport_ptr_t ptr, const void* data, size_t len) -> ssize_t {
    return len;  // Pretend that we successfully sent all the data
  });

  // We also need to provide a function for GnuTLS to write data to. We'll use a lambda function for that.
  gnutls_transport_set_pull_function(session, [](gnutls_transport_ptr_t ptr, void* data, size_t len) -> ssize_t {
    FuzzedDataProvider* stream = reinterpret_cast<FuzzedDataProvider*>(ptr);
    if (stream->remaining_bytes() == 0) {
      return 0;  // EOF
    }
    size_t read_len = stream->ConsumeIntegralInRange<size_t>(1, len);
    std::vector<uint8_t> read_data = stream->ConsumeBytes<uint8_t>(read_len);
    memcpy(data, read_data.data(), read_len);
    return read_len;
  });

  // Set the ptr to our FuzzedDataProvider
  gnutls_transport_set_ptr(session, &stream);

  // Prepare the buffer to receive data
  size_t buffer_size = stream.ConsumeIntegral<size_t>();
  std::vector<char> buffer(buffer_size);

  // Prepare the sequence number buffer
  char sequence[8];  // Sequence numbers are 8 bytes long

  // Call the function under test
  gnutls_record_recv_seq(session, buffer.data(), buffer.size(), sequence);

  // Cleanup
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}