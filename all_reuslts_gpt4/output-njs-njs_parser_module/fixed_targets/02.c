#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "njs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize parser
  njs_vm_opt_t options;
  njs_vm_opt_init(&options);

  njs_vm_t* vm = njs_vm_create(&options);
  if (vm == nullptr) {
    return 0;
  }

  njs_parser_t* parser = njs_parser_create(vm);
  if (parser == nullptr) {
    njs_vm_destroy(vm);
    return 0;
  }

  // Get module name from the fuzzer input
  std::string name_str = stream.ConsumeRandomLengthString();
  njs_str_t name;
  name.start = reinterpret_cast<u_char*>(const_cast<char*>(name_str.c_str()));
  name.length = name_str.size();

  // Call the target function
  njs_mod_t* mod = njs_parser_module(parser, &name);

  // Cleanup
  njs_parser_destroy(parser);
  njs_vm_destroy(vm);

  return 0;
}