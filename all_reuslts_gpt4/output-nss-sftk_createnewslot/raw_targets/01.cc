#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  SFTKSlotStr slot;
  SFTKObjectStr object;

  size_t slotID = stream.ConsumeIntegral<size_t>();

  (void)sftk_CreateNewSlot(&slot, slotID, &object);

  return 0;
}