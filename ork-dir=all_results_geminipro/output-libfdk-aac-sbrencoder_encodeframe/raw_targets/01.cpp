#include "sbr_enc.h"
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  SBR_ENCODER *hSbrEncoder = sbrEncoder_Open(48000, 1);
  FDK_ASSERT(hSbrEncoder != NULL);

  int samplesBufSize = 1024;
  short *samples = (short *)malloc(samplesBufSize * sizeof(short));
  FDK_ASSERT(samples != NULL);

  int sbrDataBits = 0;
  bool sbrData = 0;

  sbrEncoder_EncodeFrame(hSbrEncoder, samples, samplesBufSize, &sbrDataBits, sbrData);

  sbrEncoder_Close(hSbrEncoder);
  free(samples);
  return 0;
}