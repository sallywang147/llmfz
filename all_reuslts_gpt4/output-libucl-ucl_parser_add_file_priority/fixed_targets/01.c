#include "ucl.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  struct ucl_parser *parser = ucl_parser_new(0);

  std::string filename = provider.ConsumeRandomLengthString();
  int priority = provider.ConsumeIntegral<int>();

  // Create a temporary file and write the data to it.
  char path[] = "/tmp/fuzzingXXXXXX";
  int fd = mkstemp(path);
  if (fd < 0) {
    ucl_parser_free(parser);
    return 0;
  }

  write(fd, filename.c_str(), filename.size());
  close(fd);

  // Parse the file.
  ucl_parser_add_file_priority(parser, path, priority);

  // Clean up.
  remove(path);
  ucl_parser_free(parser);

  return 0;
}