#include <QPluginLoader>
#include <QTemporaryDir>
#include <QDir>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  QTemporaryDir temp_dir;
  QDir temp_dir_qdir(temp_dir.path());
  temp_dir_qdir.mkpath(".");

  std::vector<uint8_t> bytes = FuzzedDataProvider(data, size).ConsumeRemainingBytes();
  QString plugin_path = temp_dir_qdir.path() + QDir::separator() + QString::fromLatin1(reinterpret_cast<const char *>(bytes.data()), bytes.size());
  QFile plugin_file(plugin_path);
  plugin_file.open(QIODevice::WriteOnly);
  plugin_file.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
  plugin_file.close();

  QPluginLoader plugin_loader(plugin_path);
  bool load_result = plugin_loader.load();
  if (load_result) {
    plugin_loader.unload();
  }

  return 0;
}