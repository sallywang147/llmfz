#include <fuzzer/FuzzedDataProvider.h>
#include "sftk.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the parameters
  SFTKSlotStr slot;
  size_t len = stream.ConsumeIntegral<size_t>();
  SFTKObjectStr object;

  // Call the function to fuzz
  sftk_CreateNewSlot(&slot, len, &object);

  return 0;
}