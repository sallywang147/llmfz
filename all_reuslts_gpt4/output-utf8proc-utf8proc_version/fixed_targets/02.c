#include <utf8proc.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char* version = utf8proc_version();
  return 0;
}