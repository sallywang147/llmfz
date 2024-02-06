#include "ivorbisfile.h"
#include <cstdint>
#include <stdio.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  OggVorbis_File vf;
  int result = ov_open_memory(Data, Size, NULL, 0, &vf);
  if (result < 0) {
    return 0;
  }
  int current_section = 0;
  char pcm[4096];
  long read_result;
  while (true) {
    read_result = ov_read(&vf, pcm, sizeof(pcm), &current_section);
    if (read_result <= 0 && read_result != OV_HOLE) {
      break;
    }
  }
  ov_clear(&vf);
  return 0;
}