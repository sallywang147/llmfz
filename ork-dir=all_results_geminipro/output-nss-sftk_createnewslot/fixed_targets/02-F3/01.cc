#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "sftk.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t slot_size = provider.ConsumeIntegralInRange<size_t>(0, 1024 * 1024);
  std::vector<uint8_t> slot_data(slot_size);
  provider.ConsumeBytes<uint8_t>(slot_data.data(), slot_size);

  SFTKSlotStr slot;
  SFTKObjectStr object;
  sftk_InitSlot(&slot, slot_data.data(), slot_size);

  size_t object_size = provider.ConsumeIntegralInRange<size_t>(0, 1024 * 1024);
  std::vector<uint8_t> object_data(object_size);
  provider.ConsumeBytes<uint8_t>(object_data.data(), object_size);

  sftk_InitObject(&object, object_data.data(), object_size);

  sftk_CreateNewSlot(&slot, object_size, &object);

  // Free the allocated memory for the slot and object.
  sftk_FreeSlot(&slot);
  sftk_FreeObject(&object);

  return 0;
}