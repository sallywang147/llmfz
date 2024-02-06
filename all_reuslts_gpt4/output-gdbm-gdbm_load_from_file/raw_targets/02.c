#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need to create a temporary file to pass to gdbm_load_from_file.
  // We'll write the fuzzing input to this file.
  char filename[] = "/tmp/gdbm_fuzz.XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  FILE* fp = fdopen(fd, "w+");
  if (!fp) {
    close(fd);
    return 0;
  }

  // Write the fuzzing input to the temporary file.
  std::vector<uint8_t> fuzzing_input = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(fuzzing_input.data(), 1, fuzzing_input.size(), fp);
  rewind(fp);

  // Initialize the GDBM file info.
  struct gdbm_file_info* dbf = nullptr;

  // Initialize the other parameters for gdbm_load_from_file.
  int replace = stream.ConsumeIntegral<int>();
  int meta_mask = stream.ConsumeIntegral<int>();
  size_t line = 0;

  // Call the function under test.
  gdbm_load_from_file(&dbf, fp, replace, meta_mask, &line);

  // Clean up.
  gdbm_close(dbf);
  fclose(fp);
  remove(filename);

  return 0;
}