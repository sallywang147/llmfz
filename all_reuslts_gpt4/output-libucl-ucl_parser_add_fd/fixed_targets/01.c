#include <fuzzer/FuzzedDataProvider.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "ucl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a temporary file and write the data into it
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  write(fd, data, size);
  lseek(fd, 0, SEEK_SET);

  // Parse the file using ucl_parser_add_fd
  struct ucl_parser *parser = ucl_parser_new(0);
  bool result = ucl_parser_add_fd(parser, fd);

  // Cleanup
  ucl_parser_free(parser);
  close(fd);
  unlink(filename);

  return 0;
}