#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "vulkan/vulkan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  VkInstance inst = {0};
  char *instance_layers[] = {"VK_LAYER_KHRONOS_validation", "VK_LAYER_test_layer_1", "VK_LAYER_test_layer_2"};
  const VkApplicationInfo app = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext = NULL,
      .pApplicationName = "TEST_APP",
      .applicationVersion = 0,
      .pEngineName = "TEST_ENGINE",
      .engineVersion = 0,
      .apiVersion = VK_API_VERSION_1_0,
  };
  VkInstanceCreateInfo inst_info = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = NULL,
      .pApplicationInfo = &app,
      .enabledLayerCount = 1,
      .ppEnabledLayerNames = (const char *const *)instance_layers,
      .enabledExtensionCount = 0,
      .ppEnabledExtensionNames = NULL,
  };
  VkResult err = vkCreateInstance(&inst_info, NULL, &inst);
  if (err != VK_SUCCESS) {
    return 0;
  }

  VkDevice device = {0};
  VkDeviceCreateInfo device_info = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .pNext = NULL,
      .queueCreateInfoCount = 0,
      .pQueueCreateInfos = NULL,
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = NULL,
      .enabledExtensionCount = 0,
      .ppEnabledExtensionNames = NULL,
      .pEnabledFeatures = NULL,
  };
  err = vkCreateDevice(inst, &device_info, NULL, &device);
  if (err != VK_SUCCESS) {
    vkDestroyInstance(inst, NULL);
    return 0;
  }

  std::string proc_name = stream.ConsumeRandomLengthString();
  func_type *func = vkGetDeviceProcAddr(device, proc_name.c_str());

  vkDestroyDevice(device, NULL);
  vkDestroyInstance(inst, NULL);

  return 0;
}