#include <flatbuffers/flatbuffers.h>
#include <iostream>
#include <string>

extern "C" {
#include <stddef.h>
#include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  flatbuffers::Parser parser;
  std::string text;
  std::string json;
  flatbuffers::GenerateTextFile(&parser, &text, &json);
  return 0;
}