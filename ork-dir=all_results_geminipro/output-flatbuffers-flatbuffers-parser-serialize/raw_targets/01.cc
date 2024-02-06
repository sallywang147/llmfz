#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "flatbuffers/flatbuffers.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  flatbuffers::Parser parser;
  parser.Parse(reinterpret_cast<const uint8_t*>(input.c_str()), input.size());

  flatbuffers::Parser* parser_ptr = &parser;
  parser.Serialize(parser_ptr);
  return 0;
}