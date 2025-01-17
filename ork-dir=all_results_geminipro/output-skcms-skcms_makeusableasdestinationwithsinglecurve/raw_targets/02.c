#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t profile_size = stream.ConsumeIntegral<size_t>();
  if (profile_size == 0 || profile_size > 1024 * 1024) {
    return 0;
  }
  const uint8_t* profile_data = stream.ConsumeBytes<uint8_t>(profile_size);
  struct skcms_ICCProfile profile;
  if (skcms_Parse(&profile, profile_data, profile_size) != 0) {
    return 0;
  }
  skcms_MakeUsableAsDestinationWithSingleCurve(&profile);
  skcms_Free(&profile);
  return 0;
}