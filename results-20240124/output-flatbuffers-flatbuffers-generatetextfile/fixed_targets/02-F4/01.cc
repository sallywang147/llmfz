#include <locale.h>
#include <string>

extern "C" {
#include "flatbuffers/flatbuffers.h"
}

char * GenerateTextFile(flatbuffers::Parser *, std::string *, std::string *);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  std::string output;
  std::string binary_buffer;
  flatbuffers::Parser parser;
  auto root = parser.Parse(input.c_str(), &output, &binary_buffer);
  setlocale(LC_ALL, "");
  GenerateTextFile(root, &output, &binary_buffer);
  return 0;
}