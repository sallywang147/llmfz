#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "Alembic/AbcCoreOgawa/SprImpl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SprImpl object
  Alembic::AbcCoreOgawa::v12::SprImpl sprImpl;

  // Consume data from the fuzzer input
  size_t sampleSize = stream.ConsumeIntegral<size_t>();
  std::string sampleData = stream.ConsumeRemainingBytesAsString();

  // Ensure that the sampleData size is at least as large as sampleSize
  sampleData.resize(std::max(sampleData.size(), sampleSize), '\0');

  // Call the target function
  sprImpl.getSample(&sprImpl, sampleSize, &sampleData[0]);

  return 0;
}