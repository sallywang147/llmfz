#include "ucl.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We dont null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }
  struct ucl_parser *parser = ucl_parser_new(0);

  int pipe_fds[2];
  pipe(pipe_fds);
  write(pipe_fds[1], data, size);
  close(pipe_fds[1]);

  bool res = ucl_parser_add_fd(parser, pipe_fds[0]);
  close(pipe_fds[0]);

  if (ucl_parser_get_error(parser) != NULL) {
    return 0;
  }

  ucl_parser_free(parser);
  return 0;
}