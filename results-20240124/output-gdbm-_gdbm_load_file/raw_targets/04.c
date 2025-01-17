 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gdbm_init();
    initialized = true;
  }

  std::vector<uint8_t> input_buffer(data, data + size);
  struct dump_file* file = dump_file_open(input_buffer.data(), input_buffer.size());
  if (file == nullptr) {
    return 0;
  }

  struct gdbm_file_info* dbf = gdbm_file_info_create();
  if (dbf == nullptr) {
    dump_file_close(file);
    return 0;
  }

  int ret = _gdbm_load_file(file, dbf, nullptr, 0, 0);
  dump_file_close(file);
  gdbm_file_info_destroy(dbf);

  return ret;
}