#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "attach.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct AttachPrivateData *private_data = new AttachPrivateData;
  int ret = op_followup(private_data, 0);
  delete private_data;
  return ret;
}