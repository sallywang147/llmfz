#include <stddef.h>
#include <stdint.h>
#include <string>

#include "flatbuffers/flatbuffers.h"

extern "C" {
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"
}

namespace flatbuffers {

// Generate text output from a binary buffer and store in `text`.
char *GenerateTextFile(Parser *parser, std::string *text, std::string *error_out) {
  text->clear();
  error_out->clear();
  return GenerateText(parser, text, error_out);
}

}  // namespace flatbuffers

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  flatbuffers::Parser parser(data, size);
  std::string text, error_out;
  flatbuffers::GenerateTextFile(&parser, &text, &error_out);
  return 0;
}