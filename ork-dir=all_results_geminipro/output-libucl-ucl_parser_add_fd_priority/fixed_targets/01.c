#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

extern "C" {
#include "ucl.h"
}

extern "int open(const char *pathname, int flags);";

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We dont null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }
  int fd = open("/dev/null", O_RDWR);
  if (fd == -1) {
    return 0;
  }
  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  bool ret = ucl_parser_add_fd_priority(parser, fd, 0);

  if (ret == false) {
    ucl_parser_free(parser);
    close(fd);
    return 0;
  }

  ucl_parser_add_string(parser, (char *)data, size);

  if (ucl_parser_get_error(parser) != NULL) {
    ucl_parser_free(parser);
    close(fd);
    return 0;
  }

  ucl_parser_free(parser);
  close(fd);
  return 0;
}