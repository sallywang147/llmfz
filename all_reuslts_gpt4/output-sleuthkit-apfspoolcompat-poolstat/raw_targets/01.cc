#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "APFSPoolCompat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file for fuzzing
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  FILE* hFile = fdopen(fd, "w+");
  if (hFile == nullptr) {
    close(fd);
    return 0;
  }

  // Write the fuzzed data to the file
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(buffer.data(), 1, buffer.size(), hFile);
  fflush(hFile);
  rewind(hFile);

  // Create an instance of APFSPoolCompat
  APFSPoolCompat apfsPoolCompat;

  // Call the target function
  apfsPoolCompat.poolstat(&apfsPoolCompat, hFile);

  // Clean up
  fclose(hFile);
  remove(filename);

  return 0;
}