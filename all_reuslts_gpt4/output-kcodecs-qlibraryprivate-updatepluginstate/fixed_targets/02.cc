#include <QLibrary>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  QString libraryName = QString::fromStdString(stream.ConsumeRandomLengthString());
  QLibrary library(libraryName);
  
  // QLibraryPrivate is not directly accessible, but we can trigger its methods by manipulating QLibrary
  if (stream.ConsumeBool()) {
    library.load();
  } else {
    library.unload();
  }
  
  return 0;
}