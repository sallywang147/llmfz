#include <fuzzer/FuzzedDataProvider.h>
#include <QPluginLoader>
#include <QLibrary>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    
    QString libraryPath = QString::fromStdString(stream.ConsumeRandomLengthString());
    QLibrary library(libraryPath);
    
    QPluginLoader pluginLoader;
    pluginLoader.load(&library);
    
    return 0;
}