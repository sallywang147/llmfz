#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "APFSFSCompat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize APFSFSCompat object
  APFSFSCompat apfsfscompat;

  // Extract integral values
  int istat_flags = stream.ConsumeIntegral<int>();
  size_t inode_num = stream.ConsumeIntegral<size_t>();
  size_t numblock = stream.ConsumeIntegral<size_t>();
  int sec_skew = stream.ConsumeIntegral<int>();

  // Create a temporary file for hFile
  FILE *hFile = tmpfile();
  if (hFile == NULL) {
    return 0;
  }

  // Call the target function
  apfsfscompat.istat(&apfsfscompat, istat_flags, hFile, inode_num, numblock, sec_skew);

  // Close the temporary file
  fclose(hFile);

  return 0;
}