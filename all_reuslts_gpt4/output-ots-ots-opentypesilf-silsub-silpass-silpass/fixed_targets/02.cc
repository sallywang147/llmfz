#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "opentype-sanitiser.h"
#include "ots.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create two SILPass objects
  ots::OpenTypeSILF::SILSub::SILPass silPass1;
  ots::OpenTypeSILF::SILSub::SILPass silPass2;

  // Call the function
  silPass1.SILPass(&silPass1, &silPass2);

  return 0;
}