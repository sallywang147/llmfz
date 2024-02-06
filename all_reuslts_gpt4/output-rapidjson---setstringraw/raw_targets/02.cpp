#include <fuzzer/FuzzedDataProvider.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a rapidjson document
  rapidjson::Document doc;
  doc.SetObject();
  rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

  // Consume data from the stream to create a string
  std::string str = stream.ConsumeRandomLengthString();
  rapidjson::Value value;
  
  // Create a GenericStringRef from the string
  rapidjson::GenericStringRef<char> genericStringRef(str.c_str());

  // Call SetStringRaw on the value
  value.SetStringRaw(genericStringRef);
  
  // Add the value to the document
  doc.AddMember("key", value, allocator);

  // Serialize the document to a string buffer
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  doc.Accept(writer);

  return 0;
}