#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "flatbuffers/idl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the Parser object
  flatbuffers::IDLOptions options;
  flatbuffers::Parser parser(options);

  // Generate a string for the schema and input
  std::string schema = stream.ConsumeRandomLengthString();
  std::string input = stream.ConsumeRemainingBytesAsString();

  // Parse the schema. If it fails, return early.
  if (!parser.Parse(schema.c_str())) {
    return 0;
  }

  // Parse the input based on the schema. If it fails, return early.
  if (!parser.Parse(input.c_str())) {
    return 0;
  }

  // Generate the text file
  std::string output;
  char *result = flatbuffers::GenTextFile(&parser, &input, &output);

  // Free the result
  if (result) {
    free(result);
  }

  return 0;
}