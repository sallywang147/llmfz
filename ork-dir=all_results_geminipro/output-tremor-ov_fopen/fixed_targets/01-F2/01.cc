#include "ivorbisfile.h"
#include <cstdint>
#include <stdio.h>
#include <string.h>

extern "C" {
#include <stdlib.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  OggVorbis_File vf;
  char *path = new char[Size + 1];
  memcpy(path, Data, Size);
  path[Size] = '\0';  // Add null-terminator to make it a valid C string
  int result = ov_fopen(path, &vf);
  if (result < 0) {
    return 0;
  }
  ov_clear(&vf);
  delete[] path;
  return 0;
}