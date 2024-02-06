#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ots.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an OTSStream object
  ots::OTSStream out;

  // Create an OpenTypeGLAT_v2::GlatEntry object
  ots::OpenTypeGLAT_v2::GlatEntry glatEntry;

  // Serialize the GlatEntry object
  bool result = glatEntry.SerializePart(&glatEntry, &out);

  return 0;
}