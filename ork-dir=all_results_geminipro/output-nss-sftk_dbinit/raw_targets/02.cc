#include <fuzzer/FuzzedDataProvider.h>

#include <cstring>

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  char *path = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  char *dir = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  char *log = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  char *db = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  char *data_dir = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  char *tmp_dir = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  char *cache_dir = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  int max_db_files = provider.ConsumeIntegralInRange<int>(0, 1024);
  int max_db_size = provider.ConsumeIntegralInRange<int>(0, 1024);
  int max_log_size = provider.ConsumeIntegralInRange<int>(0, 1024);
  int max_cache_size = provider.ConsumeIntegralInRange<int>(0, 1024);
  int max_tmp_size = provider.ConsumeIntegralInRange<int>(0, 1024);
  struct SFTKDBHandleStr **db_handle;
  struct SFTKDBHandleStr **log_handle;
  size_t ret = sftk_DBInit(path, dir, log, db, data_dir, tmp_dir, cache_dir, max_db_files, max_db_size, max_log_size, max_cache_size, max_tmp_size, db_handle, log_handle);
  return ret;
}