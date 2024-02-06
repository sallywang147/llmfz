#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <rapidjson/document.h>
#include <rapidjson/memorystream.h>
#include <rapidjson/encodedstream.h>
#include <rapidjson/reader.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> allocator;

  // Consume some data for the original buffer
  size_t originalSize = stream.ConsumeIntegralInRange<size_t>(0, size);
  char* originalPtr = static_cast<char*>(allocator.Malloc(originalSize));
  if (originalPtr) {
    std::memcpy(originalPtr, stream.data(), originalSize);
  }

  // Consume remaining data for the new buffer
  size_t newSize = stream.remaining_bytes();
  char* newPtr = allocator.Realloc(originalPtr, originalSize, newSize);
  if (newPtr) {
    std::memcpy(newPtr, stream.data(), newSize);
  }

  allocator.Free(newPtr);

  return 0;
}