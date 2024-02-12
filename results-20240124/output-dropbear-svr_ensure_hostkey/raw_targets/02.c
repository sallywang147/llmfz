 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "dropbear.h"
#include "ssh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* config_file = stream.ConsumeRemainingBytesAsString().c_str();
  dropbear_loglevel = 0;
  dropbear_init(1);
  dropbear_config_load(config_file);
  svr_ensure_hostkey();
  dropbear_cleanup();
  return 0;
}