#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

// Assuming the function is defined in 'vulkan/vulkan.h'
#include <vulkan/vulkan.h>

// Assuming the device is created in 'device.h'
#include "device.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Assuming a function 'create_device' to create a device
    VkDevice_T *device = create_device();
    if (!device) {
        return 0;
    }

    // Extract a string. You MUST use .c_str() to use result as pointer
    std::string str = stream.ConsumeRandomLengthString();
    char *procName = const_cast<char*>(str.c_str());

    func_type *func = vkGetDeviceProcAddr(device, procName);

    // Assuming a function 'destroy_device' to destroy a device
    destroy_device(device);

    return 0;
}