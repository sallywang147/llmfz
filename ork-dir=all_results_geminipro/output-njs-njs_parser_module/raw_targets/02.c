#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "njs_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string module_name = stream.ConsumeRemainingBytesAsString();
  njs_str_t name;
  name.str = reinterpret_cast<uint8_t*>(const_cast<char*>(module_name.c_str()));
  name.len = module_name.size();
  njs_parser_s parser;
  njs_parser_init(&parser);
  njs_mod_s* mod = njs_parser_module(&parser, &name);
  njs_parser_free(&parser);
  if (mod != nullptr) {
    njs_mod_destroy(mod);
  }
  return 0;
}