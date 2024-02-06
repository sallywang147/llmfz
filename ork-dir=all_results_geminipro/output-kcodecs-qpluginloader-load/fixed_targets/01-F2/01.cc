#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <QPluginLoader>
#include <QLibrary>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> bytes = provider.ConsumeRemainingBytes();
  void *data_ptr = bytes.data();

  QLibrary lib(reinterpret_cast<const char *>(data_ptr));
  QPluginLoader loader(&lib);
  loader.load();

  return 0;
}