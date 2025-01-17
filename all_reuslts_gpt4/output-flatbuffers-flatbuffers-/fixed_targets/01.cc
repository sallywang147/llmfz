#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string schema_string = stream.ConsumeRandomLengthString();
  std::string json_string = stream.ConsumeRemainingBytesAsString();

  flatbuffers::IDLOptions idl_options;
  flatbuffers::Parser parser(idl_options);
  if (!parser.Parse(schema_string.c_str())) {
    return 0;
  }

  flatbuffers::(anonymous namespace)::TextCodeGenerator code_generator(&parser);
  std::string generated_code;
  std::string error_message;

  int result = flatbuffers::(flatbuffers::(anonymous namespace)::TextCodeGenerator(&code_generator, &parser, &generated_code, &error_message);

  return 0;
}