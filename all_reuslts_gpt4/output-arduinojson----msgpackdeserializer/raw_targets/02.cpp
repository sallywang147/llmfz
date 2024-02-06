#include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  using namespace ArduinoJson::V701HB4::detail;
  BoundedReader<const uint8_t*, void> reader(data, data + size);
  MsgPackDeserializer<BoundedReader<const uint8_t*, void>> deserializer(reader);
  // Destructor will be called automatically when deserializer goes out of scope
  return 0;
}