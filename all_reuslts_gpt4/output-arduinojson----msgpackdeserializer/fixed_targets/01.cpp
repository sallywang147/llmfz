#include <ArduinoJson.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a bounded reader
  ArduinoJson::V701HB4::detail::BoundedReader<const uint8_t*, void> reader(data, data + size);

  // Create a MsgPackDeserializer with the bounded reader
  ArduinoJson::V701HB4::detail::MsgPackDeserializer<ArduinoJson::V701HB4::detail::BoundedReader<const uint8_t*, void>> deserializer(reader);

  // Deserialize the data
  ArduinoJson::V701HB4::JsonDocument doc;
  deserializer.parse(doc);

  // Explicitly call the destructor
  deserializer.~MsgPackDeserializer();

  return 0;
}