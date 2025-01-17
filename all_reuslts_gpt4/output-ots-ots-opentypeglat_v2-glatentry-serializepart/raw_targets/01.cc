#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ots.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OTSStream
  ots::OTSStream out;

  // Initialize OpenTypeGLAT_v2::GlatEntry
  ots::OpenTypeGLAT_v2::GlatEntry glat_entry;

  // Call the function to fuzz
  bool result = glat_entry.SerializePart(&glat_entry, &out);

  return 0;
}