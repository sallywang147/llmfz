#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <ipp/ipp.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  char *buffer = (char *)malloc(fdp.ConsumeRemainingBytes<size_t>());
  fdp.ConsumeBytes<size_t>(buffer, fdp.ConsumeRemainingBytes<size_t>());
  struct _ipp_s *supported = ippNew();
  char *ppd = _ppdCreateFromIPP(buffer, fdp.ConsumeRemainingBytes<size_t>(), supported);
  ippDelete(supported);
  free(buffer);
  free(ppd);
  return 0;
}