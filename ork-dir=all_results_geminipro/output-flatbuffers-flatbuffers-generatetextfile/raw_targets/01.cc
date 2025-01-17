#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "flatbuffers/flatbuffers.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string schema = stream.ConsumeRemainingBytesAsString();
  flatbuffers::Parser parser;
  std::string error_message;
  std::string text_file;
  char* result = flatbuffers::GenerateTextFile(&parser, &schema, &text_file, &error_message);
  free(result);
  return 0;
}