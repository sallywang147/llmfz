#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "skcms.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct skcms_ICCProfile profile;
  struct skcms_TransferFunction inv_tf;
  
  // Initialize the profile and inv_tf with random data
  if (stream.remaining_bytes() < sizeof(profile) + sizeof(inv_tf)) {
    return 0;
  }
  
  stream.ConsumeData(&profile, sizeof(profile));
  stream.ConsumeData(&inv_tf, sizeof(inv_tf));

  // Call the target function
  skcms_TRCs_AreApproximateInverse(&profile, &inv_tf);

  return 0;
}