#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "APFSFSCompat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  APFSFSCompat fsCompat;
  int istat_flags = stream.ConsumeIntegral<int>();
  FILE *hFile = tmpfile();
  size_t inode_num = stream.ConsumeIntegral<size_t>();
  size_t numblock = stream.ConsumeIntegral<size_t>();
  int sec_skew = stream.ConsumeIntegral<int>();

  if (hFile == NULL) {
    return 0;
  }

  fsCompat.istat(&fsCompat, istat_flags, hFile, inode_num, numblock, sec_skew);

  fclose(hFile);
  return 0;
}