#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ots.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create two SILPass objects
  ots::OpenTypeSILF::SILSub::SILPass silPass1;
  ots::OpenTypeSILF::SILSub::SILPass silPass2;

  // Use the data to fill the first SILPass object
  size_t consumed = stream.ConsumeData(&silPass1, sizeof(silPass1));

  // If there was not enough data to fill the first SILPass object, return
  if (consumed != sizeof(silPass1)) {
    return 0;
  }

  // Call the function under test
  silPass2.SILPass(&silPass1);

  return 0;
}