#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "skcms.h"

extern "C" {
#include "skcms_internal.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t profile_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const uint8_t* profile_data = stream.ConsumeBytes<uint8_t>(profile_size).data();
  skcms_ICCProfile* profile_1 = skcms_ParseICCProfile(profile_data, profile_size);
  if (profile_1 == nullptr) {
    return 0;
  }

  const size_t profile_size_2 = stream.ConsumeIntegralInRange<size_t>(0, size);
  const uint8_t* profile_data_2 =
      stream.ConsumeBytes<uint8_t>(profile_size_2).data();
  skcms_ICCProfile* profile_2 =
      skcms_ParseICCProfile(profile_data_2, profile_size_2);
  if (profile_2 == nullptr) {
    skcms_FreeICCProfile(profile_1);
    return 0;
  }

  // Call the function that was not called before
  const bool result = skcms::ApproximatelyEqualProfiles(profile_1, profile_2);

  skcms_FreeICCProfile(profile_1);
  skcms_FreeICCProfile(profile_2);
  return 0;
}