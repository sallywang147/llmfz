#include <ArduinoJson.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a VariantSlot object.
  ArduinoJson::V701HB4::detail::VariantSlot variantSlot;

  // Allocate memory for the VariantSlot object.
  char* variantSlotPtr = new char[sizeof(variantSlot)];

  // Use the delete operator of the VariantSlot object.
  ArduinoJson::V701HB4::detail::VariantSlot::operator delete(variantSlotPtr, variantSlotPtr);

  return 0;
}