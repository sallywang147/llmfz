#include <fuzz_dgif.h>
#include "port/protobuf.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzz_dgif((char *)data, size);
  return 0;
}
}