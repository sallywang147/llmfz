#include <fuzzer/FuzzedDataProvider.h>
#include "ots.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(ots::OpenTypeSILF::SILSub)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  ots::OpenTypeSILF::SILSub silSub1;
  ots::OpenTypeSILF::SILSub silSub2;

  size_t consumed = stream.ConsumeData(&silSub1, sizeof(silSub1));
  if (consumed != sizeof(silSub1)) {
    return 0;
  }

  consumed = stream.ConsumeData(&silSub2, sizeof(silSub2));
  if (consumed != sizeof(silSub2)) {
    return 0;
  }

  silSub1.SILSub(&silSub2);

  return 0;
}