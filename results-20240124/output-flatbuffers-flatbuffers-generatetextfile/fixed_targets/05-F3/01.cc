#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/util.h>
#include <iostream>
#include <string>

extern "C" {
#include "fuzzer_utils.h"
}

// Fuzzer entry point
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Parse the FlatBuffers binary data.
  flatbuffers::Parser parser;
  if (!parser.Parse(data, size)) {
    std::cerr << "Failed to parse FlatBuffers binary data." << std::endl;
    return 0;
  }

  // Generate text output from the parsed data.
  std::string text;
  flatbuffers::GenerateTextFile(&parser, &text, nullptr);

  // Print the generated text output.
  std::cout << text << std::endl;

  return 0;
}