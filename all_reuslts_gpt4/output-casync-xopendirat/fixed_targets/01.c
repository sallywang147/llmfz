#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

#include "xopendirat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate a temporary file.
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd == -1) {
    return 0;
  }

  // Write the fuzzing data to the file.
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  write(fd, buffer.data(), buffer.size());

  // Close the file.
  close(fd);

  // Open the directory containing the file.
  int dirfd = open("/tmp", O_DIRECTORY);
  if (dirfd == -1) {
    return 0;
  }

  // Call the function to fuzz.
  struct __dirstream* ds;
  xopendirat(dirfd, filename, 0, &ds);

  // Clean up.
  close(dirfd);
  remove(filename);

  return 0;
}