#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "aspell.h"

extern "C" {
#include "aspell_config.h"
#include "aspell_error.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  AspellConfig config;
  AspellDictEnum enumeration;
  AspellCanHaveError err;
  aspell_create_config(&config);
  aspell_create_dict_enum(&enumeration, &config, &err);
  // Fix the function call
  aspell_create_default_dict(&err, &enumeration, &config);
  aspell_free_config(config);
  aspell_free_dict_enum(enumeration);
  return 0;
}