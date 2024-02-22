#include "sbr_enc.h"
#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include "FDK_assert.h"
}

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
```

The fix is to wrap the `#include "FDK_assert.h"` directive with `extern "C" {}`. This is necessary because the `FDK_assert.h` header contains C-style function declarations, and the compiler needs to be able to find these declarations in order to link the object files correctly.