#include "sbr_enc.h"
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  HANDLE_SBRENCODER hSbrEncoder = NULL;
  INT16 *samples = NULL;
  INT32 samplesBufSize = 0;
  INT32 *sbrDataBits = NULL;
  INT8 sbrData = 0;

  hSbrEncoder = sbrEncoder_Open();
  FDK_ASSERT(hSbrEncoder != NULL);

  const uint8_t *start = Data;
  UINT valid, buffer_size;

  do {
    valid = buffer_size = Data + Size - start;
    samplesBufSize = valid / 2;
    samples = (INT16 *)start;
    start += buffer_size - valid;
    sbrEncoder_EncodeFrame(hSbrEncoder, samples, samplesBufSize, &sbrDataBits, sbrData);
  } while (valid > 0);

  sbrEncoder_Close(hSbrEncoder);
  hSbrEncoder = NULL;
  return 0;
}