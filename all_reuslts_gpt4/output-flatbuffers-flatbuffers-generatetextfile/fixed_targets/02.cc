#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the parser
  flatbuffers::Parser parser;

  // Consume the data to create the input strings
  std::string input_string = stream.ConsumeRandomLengthString();
  std::string file_identifier = stream.ConsumeRandomLengthString();

  // Call the target function
  char* result = flatbuffers::GenerateTextFile(&parser, &input_string, &file_identifier);

  // Free the result
  if (result != nullptr) {
    free(result);
  }

  return 0;
}