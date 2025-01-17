#include <QLibrary>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a QLibrary object
  QLibrary library;

  // Load the library
  library.load();

  // Access the private implementation
  QLibraryPrivate *libraryPrivate = QLibraryPrivate::findOrCreate(library.fileName());

  // Call the function to fuzz
  libraryPrivate->isPlugin();

  // Unload the library
  library.unload();

  return 0;
}