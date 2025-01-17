 #include "ppd-private.h"
#include "ipp-private.h"
#include "string-private.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ipp_t *ipp = ippNew();
  FuzzedDataProvider stream(data, size);
  ippReadMem(ipp, stream.ConsumeRemainingBytes());
  char *ppd = _ppdCreateFromIPP2(nullptr, 0, ipp, nullptr);
  ippDelete(ipp);
  free(ppd);
  return 0;
}