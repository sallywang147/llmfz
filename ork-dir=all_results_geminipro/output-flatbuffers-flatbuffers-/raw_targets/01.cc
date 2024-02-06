#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

namespace flatbuffers {
namespace fuzzer {

// Fuzzes the provided flatbuffers schema.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string schema_data = stream.ConsumeRemainingBytesAsString();

  // Parse the schema.
  flatbuffers::Parser parser;
  auto ast = parser.Parse(schema_data.c_str());
  if (!ast) {
    return 0;
  }

  // Generate text code for the schema.
  std::string text_code;
  flatbuffers::TextCodeGenerator text_code_generator;
  text_code_generator.Generate(*ast, &text_code);

  // Generate binary code for the schema.
  std::string binary_code;
  flatbuffers::GenerateBinaryCode(*ast, &binary_code);

  return 0;
}

}  // namespace fuzzer
}  // namespace flatbuffers