#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "njs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the parser
  njs_vm_opt_t options;
  njs_vm_t *vm;
  njs_parser_t *parser;
  njs_str_t name;

  njs_vm_opt_init(&options);
  vm = njs_vm_create(&options);
  if (vm == NULL) {
    return 0;
  }

  parser = njs_parser_create(vm);
  if (parser == NULL) {
    njs_vm_destroy(vm);
    return 0;
  }

  // Extract a string for the module name
  std::string str_name = stream.ConsumeBytesAsString(stream.remaining_bytes());
  name.start = (u_char *) str_name.c_str();
  name.length = str_name.size();

  // Call the function to fuzz
  njs_mod_s *module = njs_parser_module(parser, &name);

  // Cleanup
  njs_parser_destroy(parser);
  njs_vm_destroy(vm);

  return 0;
}