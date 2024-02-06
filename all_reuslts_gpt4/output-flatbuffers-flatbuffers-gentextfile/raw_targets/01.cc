#include <fuzzer/FuzzedDataProvider.h>
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/idl.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::string schema = stream.ConsumeRandomLengthString();
  std::string json = stream.ConsumeRemainingBytesAsString();
  
  flatbuffers::IDLOptions idl_opts;
  flatbuffers::Parser parser(idl_opts);
  
  if (!parser.Parse(schema.c_str())) {
    return 0;
  }

  std::string *output = new std::string();
  std::string *error = new std::string();
  char *result = flatbuffers::GenTextFile(&parser, &json, output);
  
  if (result == nullptr) {
    delete error;
    delete output;
    return 0;
  }
  
  delete[] result;
  delete error;
  delete output;
  
  return 0;
}