#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "DummyInterface.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a DummyInterface instance
  DummyInterface dummyInterface;

  // Start packet polling
  dummyInterface.startPacketPolling(&dummyInterface);

  return 0;
}