 #include "ppd-private.h"
#include "ipp-private.h"
#include "string-private.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 10 || Size > 10240) {
    return 0;
  }

  char filename[256];
  sprintf(filename, "/tmp/libfuzzer.%d", getpid());
  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    return 0;
  }

  fwrite(Data, Size, 1, fp);
  fclose(fp);

  ipp_t *ipp = ippNew();
  ippReadIO(fp, (ipp_iocb_t)cupsFileRead, 1, NULL, ipp);
  cupsFileClose(fp);
  unlink(filename);

  char buffer[10240];
  _ppdCreateFromIPP2(buffer, sizeof(buffer), ipp, NULL);
  ippDelete(ipp);

  return 0;
}