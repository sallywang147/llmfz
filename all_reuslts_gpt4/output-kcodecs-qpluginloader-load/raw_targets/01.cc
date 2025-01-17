#include <QPluginLoader>
#include <QLibrary>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::string libraryPath = stream.ConsumeRandomLengthString();
  
  QLibrary library(QString::fromStdString(libraryPath));
  QPluginLoader pluginLoader;
  
  pluginLoader.load(&library);

  return 0;
}