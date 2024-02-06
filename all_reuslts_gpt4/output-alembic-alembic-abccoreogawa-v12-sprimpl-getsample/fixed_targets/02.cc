#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "Alembic/AbcCoreOgawa/SprImpl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // As we can't create an instance of SprImpl directly, we assume that we have a function getSprImpl() that returns a pointer to an instance of SprImpl.
  Alembic::AbcCoreOgawa::v12::SprImpl* sprImpl = getSprImpl();
  if (!sprImpl) {
    return 0;
  }

  // Consume size for the sample
  size_t sampleSize = provider.ConsumeIntegral<size_t>();

  // Consume data for the sample
  std::string sampleData = provider.ConsumeRemainingBytesAsString();

  // Call the function under test
  sprImpl->getSample(sprImpl, sampleSize, const_cast<char*>(sampleData.c_str()));

  return 0;
}