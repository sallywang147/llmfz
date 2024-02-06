#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initializing gdbm_file_info
  gdbm_file_info* dbf = nullptr;
  
  // Creating temporary file with fuzzed data
  char filename[] = "/tmp/gdbm_fuzzed_file.XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  write(fd, data, size);
  close(fd);
  
  FILE* fp = fopen(filename, "rb");
  if (!fp) {
    unlink(filename);
    return 0;
  }

  // Consuming fuzzed data for replace and meta_mask parameters
  int replace = stream.ConsumeIntegral<int>();
  int meta_mask = stream.ConsumeIntegral<int>();

  size_t line = 0;
  
  // Calling the target function
  gdbm_load_from_file(&dbf, fp, replace, meta_mask, &line);

  // Cleanup
  if (dbf) {
    gdbm_close(dbf);
  }
  fclose(fp);
  unlink(filename);

  return 0;
}