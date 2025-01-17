#include <fuzzer/FuzzedDataProvider.h>
#include "regexp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int))
    return 0;

  FuzzedDataProvider stream(data, size);
  int c = stream.ConsumeIntegral<int>();

  struct Reclass cc;
  incclasscanon(&cc, c);

  return 0;
}