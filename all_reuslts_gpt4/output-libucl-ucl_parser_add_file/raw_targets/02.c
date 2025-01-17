#include "ucl.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the fuzzed data to create a filename
  std::string filename = stream.ConsumeRandomLengthString();
  if(filename.empty()) {
    return 0;
  }

  // Create a file with the fuzzed data
  FILE *file = fopen(filename.c_str(), "wb");
  if (!file) {
    return 0;
  }

  const std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(buffer.data(), 1, buffer.size(), file);
  fclose(file);

  // Parse the file with ucl_parser_add_file
  struct ucl_parser *parser = ucl_parser_new(0);
  ucl_parser_add_file(parser, const_cast<char*>(filename.c_str()));

  // Clean up
  ucl_parser_free(parser);
  remove(filename.c_str());

  return 0;
}