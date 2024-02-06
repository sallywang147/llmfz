#include <stddef.h>
#include <stdint.h>

#include "apfs.h"

extern "C" {
#include <stdio.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  APFSFSCompat *fs;
  struct _IO_FILE *hFile;
  size_t inode_num;
  size_t numblock;
  int sec_skew;
  char result;

  fs = new APFSFSCompat();
  hFile = stdin;
  inode_num = 0;
  numblock = 0;
  sec_skew = 0;

  result = fs->istat(istat_flags, hFile, inode_num, numblock, sec_skew);

  delete fs;

  return 0;
}