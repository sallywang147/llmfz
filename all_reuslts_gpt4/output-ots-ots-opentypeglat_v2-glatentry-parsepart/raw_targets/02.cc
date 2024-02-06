#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ots.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ots::OpenTypeGLAT_v2::GlatEntry entry;
  ots::Buffer table(stream.ConsumeRemainingBytes<uint8_t>().data(), size);

  entry.ParsePart(&entry, &table);

  return 0;
}