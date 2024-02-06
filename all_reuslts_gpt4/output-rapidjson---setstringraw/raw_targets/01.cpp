#include <fuzzer/FuzzedDataProvider.h>
#include <rapidjson/document.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  rapidjson::Document doc;
  doc.SetObject();

  rapidjson::Value val;
  std::string str = stream.ConsumeRemainingBytesAsString();
  rapidjson::GenericStringRef<char> ref(str.c_str(), str.size());

  val.SetStringRaw(&ref);

  return 0;
}