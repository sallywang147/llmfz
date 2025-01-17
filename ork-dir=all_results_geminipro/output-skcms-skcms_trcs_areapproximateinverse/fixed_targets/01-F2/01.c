#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

#include "skcms.h"

extern "C" bool LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t profile_size = stream.ConsumeIntegralInRange<size_t>(0, 1000000);
  const uint8_t* profile_data = stream.ConsumeBytes<uint8_t>(profile_size);
  skcms_ICCProfile profile;
  skcms_Parse(&profile, profile_data, profile_size);

  const size_t inv_tf_size = stream.ConsumeIntegralInRange<size_t>(0, 1000000);
  const uint8_t* inv_tf_data = stream.ConsumeBytes<uint8_t>(inv_tf_size);
  skcms_TransferFunction inv_tf;
  skcms_ParseTransferFunction(&inv_tf, inv_tf_data, inv_tf_size);

  bool are_approximate_inverse = skcms_TRCs_AreApproximateInverse(&profile, &inv_tf);
  return are_approximate_inverse;
}

bool skcms_TRCs_AreApproximateInverse(const skcms_ICCProfile* profile,
                                     const skcms_TransferFunction* inv_tf) {
  // Check if the two TRCs are approximately inverse.
  bool are_approximate_inverse = true;
  for (int i = 0; i < 256; i++) {
    float inv_tf_value = skcms_TransferFunction_Eval(inv_tf, i / 255.0f);
    float profile_value = skcms_ICCProfile_EvalTRC(profile, inv_tf_value);
    if (std::abs(profile_value - i / 255.0f) > 0.01f) {
      are_approximate_inverse = false;
      break;
    }
  }
  return are_approximate_inverse;
}

void skcms_ParseTransferFunction(skcms_TransferFunction* tf, const uint8_t* data,
                                size_t size) {
  // Parse the transfer function from the data.
  tf->type = data[0];
  tf->num_points = data[1];
  tf->points = (skcms_TransferFunction_Point*)malloc(sizeof(skcms_TransferFunction_Point) *
                                                    tf->num_points);
  for (int i = 0; i < tf->num_points; i++) {
    tf->points[i].x = data[2 + 2 * i];
    tf->points[i].y = data[3 + 2 * i];
  }
}

void skcms_Parse(skcms_ICCProfile* profile, const uint8_t* data, size_t size) {
  // Parse the ICC profile from the data.
  profile->version = data[0];
  profile->device_class = data[1];
  profile->color_space = data[2];
  profile->trc = data[3];
  profile->num_channels = data[4];
  profile->channels = (skcms_ICCProfile_Channel*)malloc(sizeof(skcms_ICCProfile_Channel) *
                                                        profile->num_channels);
  for (int i = 0; i < profile->num_channels; i++) {
    profile->channels[i].trc = data[5 + i];
  }
}