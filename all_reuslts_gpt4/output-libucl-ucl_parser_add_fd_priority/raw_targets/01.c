#include "ucl.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  int fd[2];
  if (pipe(fd) == -1) {
    return 0;
  }

  // Write data to the pipe
  write(fd[1], stream.data(), stream.size());

  // Close the write end of the pipe
  close(fd[1]);

  int priority = stream.ConsumeIntegral<int>();
  ucl_parser_add_fd_priority(parser, fd[0], priority);

  if (ucl_parser_get_error(parser) != NULL) {
    close(fd[0]);
    return 0;
  }

  ucl_parser_free(parser);
  close(fd[0]);
  return 0;
}