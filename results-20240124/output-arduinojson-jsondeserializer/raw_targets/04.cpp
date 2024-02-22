 #include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  BoundedReader reader(data, size);
  ArduinoJson::V701HB4::detail::JsonDeserializer<BoundedReader> deserializer(reader);
  deserializer.read();
  return 0;
}