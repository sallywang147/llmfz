#include <locale.h>
#include <flatbuffers/flatbuffers.h>
#include <string>

extern "C" {
#include "fuzzer.h"
}

char * flatbuffers::GenTextFile(flatbuffers::Parser * parser, std::string * text, std::string * binary) {
  return nullptr;
}

int LLVMFuzzerTestOneInput(const uint8_t * data, size_t size) {
  flatbuffers::Parser parser;
  std::string text, binary;
  flatbuffers::GenTextFile(&parser, &text, &binary);
  return 0;
}