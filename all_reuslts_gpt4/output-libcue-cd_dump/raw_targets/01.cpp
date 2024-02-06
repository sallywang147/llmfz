#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "cd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Cd cdObj;

  // Assuming Cd struct has these attributes for the purpose of this example
  cdObj.id = stream.ConsumeIntegral<int>();
  cdObj.title = stream.ConsumeRandomLengthString().c_str();
  cdObj.artist = stream.ConsumeRandomLengthString().c_str();
  cdObj.genre = stream.ConsumeRandomLengthString().c_str();
  cdObj.year = stream.ConsumeIntegralInRange<int>(1900, 2022);

  cd_dump(&cdObj);

  return 0;
}