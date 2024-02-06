#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "sbr_encoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct SBR_ENCODER hSbrEncoder;
  int samplesBufSize = stream.ConsumeIntegral<int>();
  std::vector<short> samples = stream.ConsumeBytes<short>(samplesBufSize);
  int sbrDataBits = stream.ConsumeIntegral<int>();
  bool sbrData = stream.ConsumeBool();

  sbrEncoder_EncodeFrame(&hSbrEncoder, samples.data(), samplesBufSize, &sbrDataBits, sbrData);

  return 0;
}