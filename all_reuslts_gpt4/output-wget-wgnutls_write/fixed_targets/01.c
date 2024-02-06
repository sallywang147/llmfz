#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" int wgnutls_write(int fd, char * buf, int bufsize, char * arg);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create a temporary file and get the file descriptor
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd == -1) {
    return 0;
  }

  // Consume data for buf and arg
  std::string buf = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string arg = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  wgnutls_write(fd, buf.data(), buf.size(), arg.data());

  // Clean up
  close(fd);
  remove(filename);

  return 0;
}