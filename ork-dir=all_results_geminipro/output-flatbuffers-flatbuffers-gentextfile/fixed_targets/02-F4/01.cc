#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "flatbuffers/flatbuffers.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input_buffer;
  stream.ConsumeBytesAsString(&input_buffer);

  flatbuffers::Parser parser;
  std::string warnings;
  std::string errors;
  char* output = flatbuffers::GenTextFile(&parser, &input_buffer, &warnings, &errors);
  free(output);
  return 0;
}