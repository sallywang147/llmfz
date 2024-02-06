#include <fuzzer/FuzzedDataProvider.h>
#include <sys/socket.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  int sv[2];
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0,
        provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
    if (write(sv[1], next_input.data(), next_input.size()) != next_input.size()) {
      break;
    }
  }

  handle_conn_read(sv[0]);

  close(sv[0]);
  close(sv[1]);

  return 0;
}