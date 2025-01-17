#include <Qt>
#include <QLibrary>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  QLibrary lib("libQt5Core.so");
  lib.load();
  QLibraryPrivate *libPrivate = reinterpret_cast<QLibraryPrivate *>(lib.d_ptr);
  libPrivate->isPlugin();
  lib.unload();
  return 0;
}