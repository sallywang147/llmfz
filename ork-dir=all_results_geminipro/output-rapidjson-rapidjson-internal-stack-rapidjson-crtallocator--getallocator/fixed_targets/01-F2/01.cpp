#include <cstddef>
#include <cstdint>
#include <rapidjson/document.h>
#include <string>

extern "C" {
#include <rapidjson/error/en.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const std::string s(data, data + size);

  /* Parse input to rapidjson::Document */
  rapidjson::Document document;
  rapidjson::ParseResult pr = document.Parse(s.c_str());
  if (!pr) {
    fprintf(stderr, "Parse error: %s\n", GetParseError_En(pr.Code()));
    return 0;
  }

  /* Get allocator from rapidjson::Document */
  rapidjson::internal::Stack<rapidjson::CrtAllocator> *stack =
      document.GetAllocator();
  rapidjson::CrtAllocator *allocator = stack->GetAllocator();
  allocator->Free(allocator->GetRawMemory());

  return 0;
}