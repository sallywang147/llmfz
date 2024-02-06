#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "aspeller.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  acommon::PosibErr* els = new acommon::PosibErr();
  struct AspellStringEnumeration* config = new struct AspellStringEnumeration();
  acommon::Config* conf = new acommon::Config();
  aspeller::create_default_readonly_dict(els, config, conf);
  delete els;
  delete config;
  delete conf;
  return 0;
}