#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <memory>

#include "Alembic/AbcCoreOgawa/All.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize AprImpl object
  Alembic::AbcCoreOgawa::v12::AprImpl* aprImpl = new Alembic::AbcCoreOgawa::v12::AprImpl();

  // Consume data to generate size_t variable
  size_t sampleIndex = stream.ConsumeIntegral<size_t>();

  // Initialize shared_ptr
  std::shared_ptr<void> samplePtr;

  // Call the target function
  aprImpl->getSample(aprImpl, sampleIndex, &samplePtr);

  // Clean up
  delete aprImpl;

  return 0;
}