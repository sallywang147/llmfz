#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <vector>

#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> profile_a_bytes =
      stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  skcms_ICCProfile* profile_a = skcms_ICCProfile_new_from_bytes(
      profile_a_bytes.data(), profile_a_bytes.size());
  if (profile_a == nullptr) {
    return 0;
  }
  std::vector<uint8_t> profile_b_bytes =
      stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  skcms_ICCProfile* profile_b = skcms_ICCProfile_new_from_bytes(
      profile_b_bytes.data(), profile_b_bytes.size());
  if (profile_b == nullptr) {
    skcms_ICCProfile_delete(profile_a);
    return 0;
  }

  bool result = skcms_ApproximatelyEqualProfiles(profile_a, profile_b);
  skcms_ICCProfile_delete(profile_a);
  skcms_ICCProfile_delete(profile_b);
  return 0;
}