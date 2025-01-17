#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" {
#include <vulkan/vulkan.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  uint32_t version;
  vkEnumerateInstanceVersion(&version);
  return 0;
}

int vkEnumerateInstanceVersion(uint32_t* pApiVersion) {
  *pApiVersion = VK_API_VERSION_1_0;
  return VK_SUCCESS;
}