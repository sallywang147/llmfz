#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::vector<uint8_t> file_bytes = stream.ConsumeRemainingBytes();
  if (file_bytes.empty()) {
    return 0;
  }
  yaml_parser_t parser;
  yaml_parser_initialize(&parser);
  FILE* file = fmemopen(file_bytes.data(), file_bytes.size(), "r");
  if (file == nullptr) {
    yaml_parser_delete(&parser);
    return 0;
  }
  yaml_parser_set_input_file(&parser, file);
  yaml_event_t event;
  while (yaml_parser_parse(&parser, &event) == YAML_EVENT_DOCUMENT_START) {
    yaml_parser_delete_event(&event);
  }
  yaml_parser_delete(&parser);
  fclose(file);
  return 0;
}