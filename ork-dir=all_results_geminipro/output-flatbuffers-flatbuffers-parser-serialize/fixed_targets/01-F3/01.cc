#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "flatbuffers/flatbuffers.h"

extern "C" {
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"
}

namespace flatbuffers {

// This function is used by the fuzzer.
// It takes a flatbuffer schema and a fuzzed data provider,
// and generates a flatbuffer message according to the schema.
// The message is then serialized and returned as a string.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  // Parse the schema.
  std::string schema = fdp.ConsumeRandomLengthString(1024);
  Parser parser;
  auto ast = parser.Parse(schema.c_str());
  if (!ast) {
    return 0;
  }

  // Generate a message according to the schema.
  auto gen = fdp.ConsumeBool() ?
      Generator(ast, fdp.ConsumeBool() ? GeneratorOptions() :
                                        GeneratorOptions().eager_generated(true)) :
      Generator(ast, fdp.ConsumeBool() ?
                     GeneratorOptions().generate_all(true) :
                     GeneratorOptions().generate_all(true).eager_generated(true));
  auto buf = gen.Generate();

  // Serialize the message.
  Parser::Serialize(buf.data(), buf.size());

  return 0;
}

}  // namespace flatbuffers