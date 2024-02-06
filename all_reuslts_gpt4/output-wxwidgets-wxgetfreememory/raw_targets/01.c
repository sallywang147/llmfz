#include "wx/utils.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t freeMemory = wxGetFreeMemory();
  return 0;
}