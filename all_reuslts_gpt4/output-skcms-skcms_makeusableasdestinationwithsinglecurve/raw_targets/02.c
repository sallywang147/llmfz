#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  skcms_ICCProfile profile;
  if (!skcms_Parse(stream.ConsumeRemainingBytes<unsigned char>().data(), size, &profile)) {
    return 0;
  }

  skcms_MakeUsableAsDestinationWithSingleCurve(&profile);

  return 0;
}