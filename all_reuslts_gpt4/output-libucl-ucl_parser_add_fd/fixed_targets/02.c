#include <fuzzer/FuzzedDataProvider.h>
#include <ucl.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct ucl_parser *parser = ucl_parser_new(0);

  int pipefd[2];
  if (pipe(pipefd) != 0) {
    ucl_parser_free(parser);
    return 0;
  }

  // Write data to the pipe
  write(pipefd[1], stream.ConsumeRemainingBytes().data(), size);
  close(pipefd[1]);

  // Read data from the pipe
  ucl_parser_add_fd(parser, pipefd[0]);
  close(pipefd[0]);

  ucl_parser_free(parser);
  return 0;
}