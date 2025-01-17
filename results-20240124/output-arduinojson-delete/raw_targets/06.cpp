 #include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  auto alloc = new ArduinoJson::MemoryPool(4096);
  auto doc = new (alloc) ArduinoJson::V701HB4::JsonDocument(alloc);
  auto error = deserializeMsgPack(*doc, data, size);
  if (!error) {
    std::string json;
    serializeMsgPack(*doc, json);
  }
  doc->~JsonDocument();
  delete alloc;
  return 0;
}