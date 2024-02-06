#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct gdbm_file_info* dbf = nullptr;

  // Consume a string for filename
  std::string filename = stream.ConsumeRandomLengthString();
  char* filename_ptr = const_cast<char*>(filename.c_str());

  // Consume an integer for replace
  int replace = stream.ConsumeIntegral<int>();

  // Consume an integer for meta_mask
  int meta_mask = stream.ConsumeIntegral<int>();

  size_t line = 0;

  // Call the function to fuzz
  int ret = gdbm_load(&dbf, filename_ptr, replace, meta_mask, &line);

  if (dbf != nullptr) {
    gdbm_close(dbf);
  }

  return 0;
}