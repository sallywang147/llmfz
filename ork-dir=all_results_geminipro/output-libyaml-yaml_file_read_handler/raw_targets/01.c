#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string data_string = stream.ConsumeRemainingBytesAsString();
  char* data_ptr = const_cast<char*>(data_string.c_str());

  // Initialize the YAML parser.
  yaml_parser_t parser;
  if (!yaml_parser_initialize(&parser)) {
    return 0;
  }

  // Set the input buffer.
  yaml_parser_set_input_string(&parser, data_ptr, data_string.size());

  // Allocate a buffer to store the parsed YAML document.
  std::vector<char> buffer(4096);

  // Parse the YAML document.
  int done = 0;
  while (!done) {
    yaml_event_t event;
    if (!yaml_parser_parse(&parser, &event)) {
      break;
    }
    switch (event.type) {
      case YAML_STREAM_START_EVENT:
        break;
      case YAML_STREAM_END_EVENT:
        done = 1;
        break;
      case YAML_DOCUMENT_START_EVENT:
        break;
      case YAML_DOCUMENT_END_EVENT:
        break;
      case YAML_ALIAS_EVENT:
        break;
      case YAML_SCALAR_EVENT:
        break;
      case YAML_SEQUENCE_START_EVENT:
        break;
      case YAML_SEQUENCE_END_EVENT:
        break;
      case YAML_MAPPING_START_EVENT:
        break;
      case YAML_MAPPING_END_EVENT:
        break;
    }
    yaml_event_delete(&event);
  }

  // Clean up the YAML parser.
  yaml_parser_delete(&parser);

  return 0;
}