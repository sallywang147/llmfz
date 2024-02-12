#include "third_party/protobuf/src/google/protobuf/port_def.inc"
#include "fuzz_dgif_ala_android.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzz_dgif_ala_android((char *)data, size);
  return 0;
}