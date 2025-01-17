#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  skcms_Curve curve;
  skcms_TransferFunction inv_tf;

  // Initialize curve
  curve.table_entries = stream.ConsumeIntegral<size_t>();
  curve.table_8       = nullptr;
  curve.table_16      = nullptr;
  curve.parametric.a  = stream.ConsumeFloatingPoint<float>();
  curve.parametric.b  = stream.ConsumeFloatingPoint<float>();
  curve.parametric.c  = stream.ConsumeFloatingPoint<float>();
  curve.parametric.d  = stream.ConsumeFloatingPoint<float>();
  curve.parametric.e  = stream.ConsumeFloatingPoint<float>();
  curve.parametric.f  = stream.ConsumeFloatingPoint<float>();
  curve.parametric.g  = stream.ConsumeFloatingPoint<float>();

  // Initialize inv_tf
  inv_tf.g = stream.ConsumeFloatingPoint<float>();
  inv_tf.a = stream.ConsumeFloatingPoint<float>();
  inv_tf.b = stream.ConsumeFloatingPoint<float>();
  inv_tf.c = stream.ConsumeFloatingPoint<float>();
  inv_tf.d = stream.ConsumeFloatingPoint<float>();
  inv_tf.e = stream.ConsumeFloatingPoint<float>();
  inv_tf.f = stream.ConsumeFloatingPoint<float>();

  // Call the function to fuzz
  skcms_AreApproximateInverses(&curve, &inv_tf);

  return 0;
}