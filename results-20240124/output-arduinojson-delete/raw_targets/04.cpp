 #include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V701HB4::detail::VariantSlot::operator delete(nullptr, nullptr);
  return 0;
}