#include <fuzzer/FuzzedDataProvider.h>

#include <libconfig.h>
#include <stdlib.h>
#include <string.h>

bool load_files_section(struct private_settings_t * this, char * pattern, bool merge, char * key) {
  config_t cfg;
  config_init(&cfg);
  config_set_include_dir(&cfg, "/etc");
  config_read_file(&cfg, pattern);
  if (merge) {
    config_set_merge(&cfg, CONFIG_MERGE_APPEND);
  }
  config_lookup_string(&cfg, key, (const char **)&this->value);
  config_destroy(&cfg);
  return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct private_settings_t this;
  this.value = NULL;

  size_t pattern_len = provider.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<uint8_t> pattern_bytes = provider.ConsumeBytes<uint8_t>(pattern_len);
  char *pattern = reinterpret_cast<char *>(pattern_bytes.data());

  bool merge = provider.ConsumeBool();

  size_t key_len = provider.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<uint8_t> key_bytes = provider.ConsumeBytes<uint8_t>(key_len);
  char *key = reinterpret_cast<char *>(key_bytes.data());

  load_files_section(&this, pattern, merge, key);

  free(this.value);
  return 0;
}