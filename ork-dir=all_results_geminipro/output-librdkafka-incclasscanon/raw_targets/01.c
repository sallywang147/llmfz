#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "reclass.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int c = stream.ConsumeIntegral<int>();
  struct Reclass* cc = reclass_new(0);
  const int result = incclasscanon(cc, c);
  reclass_free(cc);
  return result;
}