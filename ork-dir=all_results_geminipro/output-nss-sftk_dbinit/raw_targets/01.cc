#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "sftk.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  char* db_path = provider.ConsumeRandomLengthString().c_str();
  char* db_name = provider.ConsumeRandomLengthString().c_str();
  char* db_type = provider.ConsumeRandomLengthString().c_str();
  char* db_user = provider.ConsumeRandomLengthString().c_str();
  char* db_password = provider.ConsumeRandomLengthString().c_str();
  char* db_host = provider.ConsumeRandomLengthString().c_str();
  char* db_port = provider.ConsumeRandomLengthString().c_str();

  int db_timeout = provider.ConsumeIntegral<int>();
  int db_retries = provider.ConsumeIntegral<int>();
  int db_max_connections = provider.ConsumeIntegral<int>();
  int db_min_connections = provider.ConsumeIntegral<int>();
  int db_connection_lifetime = provider.ConsumeIntegral<int>();

  struct SFTKDBHandleStr* db_handle = nullptr;
  struct SFTKDBHandleStr* db_handle2 = nullptr;

  size_t ret = sftk_DBInit(db_path, db_name, db_type, db_user, db_password, db_host, db_port,
                            db_timeout, db_retries, db_max_connections, db_min_connections,
                            db_connection_lifetime, &db_handle, &db_handle2);

  if (db_handle != nullptr) {
    sftk_DBClose(db_handle);
  }
  if (db_handle2 != nullptr) {
    sftk_DBClose(db_handle2);
  }

  return ret;
}