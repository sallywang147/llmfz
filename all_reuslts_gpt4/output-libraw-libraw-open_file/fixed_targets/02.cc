#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libraw/libraw.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the data to it.
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  size_t data_size = stream.remaining_bytes();
  auto data_buffer = stream.ConsumeRemainingBytes<uint8_t>();
  if (write(fd, data_buffer.data(), data_size) != static_cast<ssize_t>(data_size)) {
    close(fd);
    remove(filename);
    return 0;
  }
  close(fd);

  // Use the temporary file as input to LibRaw::open_file.
  LibRaw processor;
  processor.open_file(filename);

  // Clean up.
  remove(filename);

  return 0;
}