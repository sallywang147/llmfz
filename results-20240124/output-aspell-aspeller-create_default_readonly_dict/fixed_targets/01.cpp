#include <aspell.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <acommon/acommon.h>
#include <acommon/config.h>
#include <acommon/errno.h>
#include <acommon/posixerr.h>
}

using namespace aspell;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  acommon::PosibErr els;
  AspellConfig config;
  acommon::Config *cfg = config.get_config();
  create_default_readonly_dict(&els, &config.string_enum, cfg);
  return 0;
}