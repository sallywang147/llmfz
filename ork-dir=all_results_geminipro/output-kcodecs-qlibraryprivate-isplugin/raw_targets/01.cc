#include <Qt>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  QLibraryPrivate lib;
  lib.isPlugin();
  return 0;
}