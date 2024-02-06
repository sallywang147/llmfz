#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unistd.h>

extern "C" int wgnutls_read(int fd, char * buf, int bufsize, char * arg, double timeout);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a pipe
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    return 0;
  }

  // Write fuzzing data to the write end of the pipe
  auto buf = stream.ConsumeBytes<char>(stream.remaining_bytes());
  write(pipefd[1], buf.data(), buf.size());
  close(pipefd[1]); // Close write end

  // Prepare buffer for reading
  char read_buf[1024];
  int bufsize = sizeof(read_buf);

  // Prepare other parameters
  char arg = stream.ConsumeIntegral<char>();
  double timeout = stream.ConsumeFloatingPoint<double>();

  // Call the function to fuzz
  wgnutls_read(pipefd[0], read_buf, bufsize, &arg, timeout);

  // Clean up
  close(pipefd[0]); // Close read end

  return 0;
}