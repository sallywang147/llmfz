#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "APFSPoolCompat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an instance of APFSPoolCompat
  APFSPoolCompat apfsPoolCompat;

  // Create a temporary file
  FILE* hFile = tmpfile();
  if (hFile == nullptr) {
    return 0;
  }

  // Write the fuzzed data to the temporary file
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(buffer.data(), 1, buffer.size(), hFile);

  // Reset the file position to the beginning
  rewind(hFile);

  // Call the function to be fuzzed
  apfsPoolCompat.poolstat(&apfsPoolCompat, hFile);

  // Close the temporary file
  fclose(hFile);

  return 0;
}