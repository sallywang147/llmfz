#include <liboqs/settings.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct settings_t *settings;
  FuzzedDataProvider provider(data, size);
  size_t settings_len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char *settings_str = provider.ConsumeBytesAsString(settings_len).c_str();
  settings = settings_create_string(settings_str);
  settings_destroy(settings);
  return 0;
}