#include <fuzzer/FuzzedDataProvider.h>
#include <sys/socket.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int sv[2];

  // Create a pair of connected sockets
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
    return 0;
  }

  // Write the fuzzing data to one end of the socket pair
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  write(sv[0], buffer.data(), buffer.size());

  // Call the function to be fuzzed with the other end of the socket pair
  handle_conn_read(sv[1]);

  // Close the sockets
  close(sv[0]);
  close(sv[1]);

  return 0;
}