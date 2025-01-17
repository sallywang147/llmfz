#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "sftk.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct SFTKSlotStr* slot = nullptr;
  size_t slot_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  struct SFTKObjectStr* object = nullptr;
  size_t object_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);

  sftk_CreateNewSlot(slot, slot_size, object);

  return 0;
}