#include <flatbuffers/flatbuffers.h>
#include <string>

extern "C" char * flatbuffers::GenerateTextFile(flatbuffers::Parser * parser, std::string * text, std::string * binary) {
  return flatbuffers::GenerateTextFile(parser, text, binary);
}