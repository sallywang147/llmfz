#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "rapidjson/memorybuffer.h"
#include "rapidjson/memorystream.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the memory pool allocator
  rapidjson::MemoryPoolAllocator<> allocator;

  // Consume data for originalSize and newSize
  size_t originalSize = stream.ConsumeIntegral<size_t>();
  size_t newSize = stream.ConsumeIntegral<size_t>();

  // Allocate memory for originalPtr
  char* originalPtr = (char*)allocator.Malloc(originalSize);
  if (originalPtr == nullptr) {
    return 0;
  }

  // Fill originalPtr with data from the stream
  size_t dataSize = stream.remaining_bytes() < originalSize ? stream.remaining_bytes() : originalSize;
  std::memcpy(originalPtr, stream.ConsumeBytes<char>(dataSize).data(), dataSize);

  // Call the target function
  char* newPtr = allocator.Realloc(originalPtr, originalSize, newSize);

  // Free the allocated memory
  allocator.Free(newPtr);

  return 0;
}