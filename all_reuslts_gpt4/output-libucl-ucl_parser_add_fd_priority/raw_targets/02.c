#include <fuzzer/FuzzedDataProvider.h>
#include "ucl.h"
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  // Create a temporary file and write the data into it.
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  write(fd, data, size);
  lseek(fd, 0, SEEK_SET);

  // Consume an integer from the data to use as the priority.
  int priority = stream.ConsumeIntegral<int>();

  // Call the function under test.
  ucl_parser_add_fd_priority(parser, fd, priority);

  // Clean up.
  ucl_parser_free(parser);
  close(fd);
  unlink(filename);

  return 0;
}