#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the data into it.
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  write(fd, data, size);
  close(fd);

  // Open the temporary file with op_open_file.
  int error;
  OggOpusFile *of = op_open_file(filename, &error);

  // If the file was opened successfully, close it.
  if (of != nullptr) {
    op_free(of);
  }

  // Delete the temporary file.
  remove(filename);

  return 0;
}