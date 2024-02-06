#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  skcms_ICCProfile profile;
  skcms_TransferFunction inv_tf;

  // Initialize profile with random data
  std::vector<uint8_t> profile_data = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2);
  if (!skcms_Parse(profile_data.data(), profile_data.size(), &profile)) {
    return 0;
  }

  // Initialize inv_tf with random data
  inv_tf.g = stream.ConsumeFloatingPoint<float>();
  inv_tf.a = stream.ConsumeFloatingPoint<float>();
  inv_tf.b = stream.ConsumeFloatingPoint<float>();
  inv_tf.c = stream.ConsumeFloatingPoint<float>();
  inv_tf.d = stream.ConsumeFloatingPoint<float>();
  inv_tf.e = stream.ConsumeFloatingPoint<float>();
  inv_tf.f = stream.ConsumeFloatingPoint<float>();

  // Call the target function
  skcms_TRCs_AreApproximateInverse(&profile, &inv_tf);

  return 0;
}