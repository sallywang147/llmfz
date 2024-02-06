#include <fuzzer/FuzzedDataProvider.h>
#include <flatbuffers/idl.h>
#include <flatbuffers/util.h>
#include <flatbuffers/code_generators.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  flatbuffers::IDLOptions idl_opts;
  flatbuffers::Parser parser(idl_opts);
  std::string code;
  std::string parser_error;

  flatbuffers::TextCodeGenerator code_generator(&parser, &code, &parser_error);

  std::string schema = stream.ConsumeRemainingBytesAsString();
  if (!parser.Parse(schema.c_str())) {
    return 0;
  }

  flatbuffers::(flatbuffers::(anonymous namespace)::TextCodeGenerator * , flatbuffers::Parser * , std::string * , std::string * )(&code_generator, &parser, &code, &parser_error);

  return 0;
}