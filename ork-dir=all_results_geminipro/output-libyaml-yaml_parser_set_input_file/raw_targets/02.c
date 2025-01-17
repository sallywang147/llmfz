#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  yaml_parser_t parser;
  const int input_size = stream.ConsumeIntegralInRange<int>(0, 1024);
  const std::string input_string = stream.ConsumeRemainingBytesAsString();
  FILE* input_file = fmemopen(const_cast<char*>(input_string.c_str()), input_size,
                             "r");
  if (input_file == nullptr) {
    return 0;
  }
  yaml_parser_initialize(&parser);
  yaml_parser_set_input_file(&parser, input_file);
  yaml_token_t token;
  while (yaml_parser_scan(&parser, &token) != YAML_SCAN_DONE) {
    yaml_token_delete(&token);
  }
  yaml_parser_delete(&parser);
  fclose(input_file);
  return 0;
}