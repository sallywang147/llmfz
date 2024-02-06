#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <memory>

#include "Alembic/AbcCoreOgawa/v12/AprImpl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an instance of AprImpl
  Alembic::AbcCoreOgawa::v12::AprImpl instance;

  // Consume data from the fuzzer input
  size_t sampleIndex = stream.ConsumeIntegral<size_t>();

  // Initialize a shared_ptr
  std::shared_ptr<void> samplePtr;

  // Call the function to fuzz
  instance.getSample(&instance, sampleIndex, &samplePtr);

  return 0;
}