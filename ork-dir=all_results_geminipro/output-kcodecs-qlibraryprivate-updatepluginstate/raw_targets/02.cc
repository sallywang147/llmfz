#include <QCoreApplication>
#include <QPluginLoader>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  QCoreApplication app(0, nullptr);
  QDir dir(QDir::tempPath());
  QString temp_plugin_path = dir.absolutePath() + "/libpluginXXXXXX.so";
  QFile file(temp_plugin_path);
  file.open(QIODevice::WriteOnly);
  file.write((const char *)data, size);
  file.close();

  QPluginLoader loader(temp_plugin_path);
  QObject *plugin = loader.instance();
  if (plugin) {
    QLibraryPrivate *d = reinterpret_cast<QLibraryPrivate *>(loader.d_func());
    d->updatePluginState(d);
  }

  file.remove();

  return 0;
}