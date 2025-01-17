#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "cups-private.h"
#include "ipp-private.h"
#include "ppd-private.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 10 || size > 10240) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  size_t bufsize = provider.ConsumeIntegralInRange<size_t>(10, 10240);
  std::vector<char> buffer(bufsize);

  ipp_t *supported = ippNew();
  const size_t ipp_size = provider.ConsumeIntegralInRange<size_t>(10, 10240);
  std::vector<char> ipp_data(ipp_size);
  provider.ConsumeBytes<char>(ipp_data.data(), ipp_size);
  ippReadMem(supported, ipp_data.data(), ipp_size);

  char *result = _ppdCreateFromIPP(buffer.data(), bufsize, supported);
  ippDelete(supported);
  free(result);

  return 0;
}