#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "skcms.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t curve_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  union skcms_Curve curve;
  curve.bytes = new uint8_t[curve_size];
  stream.ConsumeBytes<uint8_t>(curve.bytes, curve_size);

  const size_t inv_tf_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct skcms_TransferFunction inv_tf;
  inv_tf.bytes = new uint8_t[inv_tf_size];
  stream.ConsumeBytes<uint8_t>(inv_tf.bytes, inv_tf_size);

  bool are_approximate_inverses = skcms_AreApproximateInverses(&curve, &inv_tf);

  delete[] curve.bytes;
  delete[] inv_tf.bytes;
  return 0;
}