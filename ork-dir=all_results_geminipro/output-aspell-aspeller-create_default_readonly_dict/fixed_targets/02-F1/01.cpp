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
  acommon::PosibErr els;
  AspellStringEnumeration config;
  acommon::Config cfg;
  aspeller::create_default_readonly_dict(&els, &config, &cfg);
  return 0;
}