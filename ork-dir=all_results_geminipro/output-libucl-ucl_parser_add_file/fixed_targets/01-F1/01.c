#include "ucl.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

extern "C" {
#include <stdlib.h>
#include <string.h>
}

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

  std::string filename = "/tmp/ucl_parser_add_file_XXXXXX";
  int fd = mkstemp(&filename[0]);
  if (fd < 0) {
    perror("mkstemp");
    return 0;
  }
  if (write(fd, data, size) < 0) {
    perror("write");
    return 0;
  }
  close(fd);

  bool ret = ucl_parser_add_file(parser, (char *)filename.c_str());

  if (ucl_parser_get_error(parser) != NULL) {
    return 0;
  }

  ucl_parser_free(parser);
  unlink(filename.c_str());
  return 0;
}