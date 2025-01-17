#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "sbr_encoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SBR Encoder
  struct SBR_ENCODER *hSbrEncoder = sbrEncoder_Init();

  // Extract samples
  size_t samplesBufSize = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<short> samples = stream.ConsumeBytes<short>(samplesBufSize);
  short *samples_ptr = samples.data();

  // Extract sbrDataBits
  int sbrDataBits = stream.ConsumeIntegral<int>();

  // Extract sbrData
  bool sbrData = stream.ConsumeBool();

  // Call the function under test
  sbrEncoder_EncodeFrame(hSbrEncoder, samples_ptr, samplesBufSize, &sbrDataBits, sbrData);

  // Cleanup
  sbrEncoder_Close(hSbrEncoder);

  return 0;
}