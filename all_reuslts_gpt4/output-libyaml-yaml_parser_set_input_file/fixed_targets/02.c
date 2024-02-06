#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string str = provider.ConsumeRemainingBytesAsString();

  FILE *file = fmemopen((void *)str.c_str(), str.size(), "r");
  if (!file) {
    return 0;
  }

  yaml_parser_t parser;
  if (!yaml_parser_initialize(&parser)) {
    fclose(file);
    return 0;
  }

  yaml_parser_set_input_file(&parser, file);

  yaml_event_t event;
  while (yaml_parser_parse(&parser, &event)) {
    if (event.type == YAML_STREAM_END_EVENT) {
      yaml_event_delete(&event);
      break;
    }
    yaml_event_delete(&event);
  }

  yaml_parser_delete(&parser);
  fclose(file);

  return 0;
}