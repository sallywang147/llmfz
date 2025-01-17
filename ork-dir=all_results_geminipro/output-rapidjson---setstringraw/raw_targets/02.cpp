#include <cstddef>
#include <cstdint>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <string>

#ifdef MSAN
extern "C" {
void __msan_check_mem_is_initialized(const volatile void *x, size_t size);
}
#endif

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const std::string s(data, data + size);

  /* Parse input to rapidjson::Document */
  rapidjson::Document document;
  rapidjson::ParseResult pr = document.Parse(s.c_str());
  if (!pr) {
    return 0;
  }

  /* Convert from rapidjson::Document to string */
  rapidjson::StringBuffer sb;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
  document.Accept(writer);
  std::string str = sb.GetString();
#ifdef MSAN
  if (str.size()) {
    __msan_check_mem_is_initialized(str.data(), str.size());
  }
#endif

  /* Create a rapidjson::Value */
  rapidjson::Value value;

  /* Set the string value to the rapidjson::Value */
  rapidjson::GenericStringRef<rapidjson::UTF8<char>> generic_string_ref(
      str.c_str(), str.size());
  value.SetStringRaw(&generic_string_ref);

  /* Convert from rapidjson::Value to string */
  rapidjson::StringBuffer sb2;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer2(sb2);
  value.Accept(writer2);
  std::string str2 = sb2.GetString();
#ifdef MSAN
  if (str2.size()) {
    __msan_check_mem_is_initialized(str2.data(), str2.size());
  }
#endif

  return 0;
}