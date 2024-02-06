#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the fuzzing input to it.
  FILE* tmp_file = tmpfile();
  if (!tmp_file) {
    return 0;
  }
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(buffer.data(), 1, buffer.size(), tmp_file);
  rewind(tmp_file);

  // Initialize the parser and set the input file.
  yaml_parser_t parser;
  if (!yaml_parser_initialize(&parser)) {
    fclose(tmp_file);
    return 0;
  }
  yaml_parser_set_input_file(&parser, tmp_file);

  // Parse the document.
  yaml_event_t event;
  while (yaml_parser_parse(&parser, &event)) {
    if (event.type == YAML_STREAM_END_EVENT) {
      yaml_event_delete(&event);
      break;
    }
    yaml_event_delete(&event);
  }

  // Clean up.
  yaml_parser_delete(&parser);
  fclose(tmp_file);

  return 0;
}