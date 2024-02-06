#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  union skcms_Curve curve;
  struct skcms_TransferFunction inv_tf;
  skcms_Curve_init(&curve);
  skcms_TransferFunction_init(&inv_tf);

  const size_t curve_size = stream.ConsumeIntegralInRange<size_t>(0, 256);
  const uint8_t* curve_data = stream.ConsumeBytes<uint8_t>(curve_size);
  skcms_Curve_setData(&curve, curve_data, curve_size);

  const size_t inv_tf_size =
      stream.ConsumeIntegralInRange<size_t>(0, 256);
  const uint8_t* inv_tf_data = stream.ConsumeBytes<uint8_t>(inv_tf_size);
  skcms_TransferFunction_setData(&inv_tf, inv_tf_data, inv_tf_size);

  const bool result = skcms_AreApproximateInverses(&curve, &inv_tf);

  skcms_Curve_destroy(&curve);
  skcms_TransferFunction_destroy(&inv_tf);
  return 0;
}