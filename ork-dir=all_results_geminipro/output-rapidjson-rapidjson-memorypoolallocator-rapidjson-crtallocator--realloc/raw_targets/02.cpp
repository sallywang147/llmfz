#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <string>

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

  /* Allocate memory for string */
  rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> allocator;
  char *ptr = allocator.Realloc(nullptr, 0, str.size() + 1);
  if (ptr == nullptr) {
    return 0;
  }

  /* Copy string to allocated memory */
  memcpy(ptr, str.c_str(), str.size() + 1);

  /* Deallocate memory */
  allocator.Free(ptr);

  return 0;
}