#include <fuzzer/FuzzedDataProvider.h>
#include <rapidjson/internal/stack.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the stack with an allocator
  rapidjson::CrtAllocator allocator;
  rapidjson::internal::Stack<rapidjson::CrtAllocator> stack(&allocator);

  // Call the function to fuzz
  rapidjson::CrtAllocator * result = stack.GetAllocator();

  return 0;
}