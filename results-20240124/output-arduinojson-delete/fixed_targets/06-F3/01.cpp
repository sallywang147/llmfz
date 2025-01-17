#include <ArduinoJson.h>

extern "C" {
#include <msgpack.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  using namespace ArduinoJson::V702HB4;

  auto alloc = new MemoryPool(4096);
  auto doc = new (alloc) JsonDocument(alloc);
  auto error = deserializeMsgPack(*doc, data, size);
  if (!error) {
    std::string json;
    serializeMsgPack(*doc, json);
  }
  doc->~JsonDocument();
  delete alloc;
  return 0;
}