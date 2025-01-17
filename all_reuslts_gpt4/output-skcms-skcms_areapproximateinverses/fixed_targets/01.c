#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);
    
    skcms_Curve curve;
    skcms_TransferFunction inv_tf;

    curve.table_entries = fuzzed_data.ConsumeIntegral<uint32_t>();
    curve.table_8       = nullptr;
    curve.table_16      = nullptr;
    curve.parametric.a  = fuzzed_data.ConsumeFloatingPoint<float>();
    curve.parametric.b  = fuzzed_data.ConsumeFloatingPoint<float>();
    curve.parametric.c  = fuzzed_data.ConsumeFloatingPoint<float>();
    curve.parametric.d  = fuzzed_data.ConsumeFloatingPoint<float>();
    curve.parametric.e  = fuzzed_data.ConsumeFloatingPoint<float>();
    curve.parametric.f  = fuzzed_data.ConsumeFloatingPoint<float>();
    curve.parametric.g  = fuzzed_data.ConsumeFloatingPoint<float>();

    inv_tf.g = fuzzed_data.ConsumeFloatingPoint<float>();
    inv_tf.a = fuzzed_data.ConsumeFloatingPoint<float>();
    inv_tf.b = fuzzed_data.ConsumeFloatingPoint<float>();
    inv_tf.c = fuzzed_data.ConsumeFloatingPoint<float>();
    inv_tf.d = fuzzed_data.ConsumeFloatingPoint<float>();
    inv_tf.e = fuzzed_data.ConsumeFloatingPoint<float>();
    inv_tf.f = fuzzed_data.ConsumeFloatingPoint<float>();

    skcms_AreApproximateInverses(&curve, &inv_tf);

    return 0;
}