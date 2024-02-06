#include "ucl.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We dont null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }
  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  // Create a pipe.
  int pipe_fds[2];
  if (pipe(pipe_fds) == -1) {
    perror("pipe");
    return 0;
  }

  // Write the data to the pipe.
  if (write(pipe_fds[1], data, size) == -1) {
    perror("write");
    return 0;
  }

  // Add the pipe to the parser.
  if (!ucl_parser_add_fd_priority(parser, pipe_fds[0], 0)) {
    perror("ucl_parser_add_fd_priority");
    return 0;
  }

  // Parse the data.
  if (ucl_parser_get_error(parser) != NULL) {
    return 0;
  }

  // Clean up.
  ucl_parser_free(parser);
  close(pipe_fds[0]);
  close(pipe_fds[1]);

  return 0;
}