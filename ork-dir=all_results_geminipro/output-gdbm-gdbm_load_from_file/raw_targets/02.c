#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include <gdbm.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRemainingBytesAsString();
  std::fstream file(filename.c_str(), std::ios::in | std::ios::binary);
  if (!file.is_open()) {
    return 0;
  }

  struct gdbm_file_info* db_file_info = nullptr;
  int replace = stream.ConsumeIntegral<int>();
  int meta_mask = stream.ConsumeIntegral<int>();
  size_t line = 0;
  int result = gdbm_load_from_file(&db_file_info, file, replace, meta_mask, &line);
  if (result != 0) {
    std::cerr << "gdbm_load_from_file failed with error code " << result
              << " at line " << line << std::endl;
  }
  file.close();
  if (db_file_info != nullptr) {
    gdbm_close(db_file_info);
  }
  return 0;
}