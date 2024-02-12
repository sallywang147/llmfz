 #include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V701HB4::detail::VariantSlot v;
  ::operator delete(v.get(), v.get());
  return 0;
}