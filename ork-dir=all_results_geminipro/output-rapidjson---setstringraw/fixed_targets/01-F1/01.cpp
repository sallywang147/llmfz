#include <cstddef>
#include <cstdint>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <string>

#ifdef MSAN
extern "C" {
#include <sanitizer/msan_interface.h>
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

  /* Set string to rapidjson::GenericValue */
  rapidjson::GenericValue<rapidjson::UTF8<char>,
                          rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>
      value;
  rapidjson::GenericStringRef<rapidjson::UTF8<char>> str_ref(str.c_str(),
                                                              str.size());
  value.SetStringRaw(&str_ref);

  return 0;
}