#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t profile_size = stream.ConsumeIntegralInRange<size_t>(0, 1000000);
  const uint8_t* profile_data = stream.ConsumeBytes<uint8_t>(profile_size);
  skcms_ICCProfile profile;
  skcms_Parse(&profile, profile_data, profile_size);

  const size_t inv_tf_size = stream.ConsumeIntegralInRange<size_t>(0, 1000000);
  const uint8_t* inv_tf_data = stream.ConsumeBytes<uint8_t>(inv_tf_size);
  skcms_TransferFunction inv_tf;
  skcms_ParseTransferFunction(&inv_tf, inv_tf_data, inv_tf_size);

  skcms_TRCs_AreApproximateInverse(&profile, &inv_tf);
  return 0;
}