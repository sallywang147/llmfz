#include <libssh2.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize libssh2
  libssh2_init(0);

  // Create a dummy session and channel for testing
  LIBSSH2_SESSION *session = libssh2_session_init();
  LIBSSH2_CHANNEL *channel = libssh2_channel_open_session(session);

  // Consume data from the stream to use as parameters
  int stream_id = stream.ConsumeIntegral<int>();
  size_t buflen = stream.remaining_bytes();
  char *buf = new char[buflen];

  // Call the function to fuzz
  libssh2_channel_read_ex(channel, stream_id, buf, buflen);

  // Clean up
  delete[] buf;
  libssh2_channel_free(channel);
  libssh2_session_free(session);
  libssh2_exit();

  return 0;
}