#include <acommon/acommon.h>
#include <aspeller/aspeller.h>

extern "C" {
#include <aspeller/aspeller.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  acommon::PosibErr els;
  AspellStringEnumeration config;
  acommon::Config cfg;
  aspeller::create_default_readonly_dict(&els, &config, &cfg);
  return 0;
}