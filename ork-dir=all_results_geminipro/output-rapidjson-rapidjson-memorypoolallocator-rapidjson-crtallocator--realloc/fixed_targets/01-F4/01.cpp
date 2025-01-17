#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <string>

#ifdef MSAN
extern "C" {
void __msan_check_mem_is_initialized(const volatile void *x, size_t size);
}
#endif

extern "C" void strcpy(char *dest, const char *src);

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

  /* Allocate memory using rapidjson::MemoryPoolAllocator */
  rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> allocator;
  char *ptr = allocator.Realloc(nullptr, 0, str.size() + 1);
  if (ptr == nullptr) {
    return 0;
  }
  strcpy(ptr, str.c_str());

  /* Free memory using rapidjson::MemoryPoolAllocator */
  allocator.Free(ptr);

  return 0;
}