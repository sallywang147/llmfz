#include <locale.h>
#include <string>

extern "C" {
#include "flatbuffers/flatc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string text;
  std::string binary;
  setlocale(LC_ALL, "");
  flatbuffers::Parser parser;
  parser.Parse(data, size);
  flatbuffers::GenTextFile(&parser, &text, &binary);
  return 0;
}