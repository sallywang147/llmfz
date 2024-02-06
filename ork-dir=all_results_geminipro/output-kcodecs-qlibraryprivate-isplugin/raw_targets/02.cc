#include <QLibrary>
#include <QLibraryPrivate>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  QLibraryPrivate *lib = new QLibraryPrivate();
  lib->isPlugin(lib);
  delete lib;
  return 0;
}