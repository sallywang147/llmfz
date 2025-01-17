extern "C" {
#include <locale.h>
#include "flatbuffers/code_generators.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  flatbuffers::Parser parser;
  parser.Parse(data, size);
  std::string text;
  std::string filename;
  char *output = flatbuffers::GenTextFile(&parser, &text, &filename);
  free(output);
  return 0;
}