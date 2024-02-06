#include <fuzzer/FuzzedDataProvider.h>
#include <libusb.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize libusb context
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) {
        return 0;
    }

    // Set libusb debug level
    libusb_set_debug(ctx, 0);

    // Open a device handle
    libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(ctx, 0x046d, 0xc52b);
    if(dev_handle == NULL) {
        libusb_exit(ctx);
        return 0;
    }

    // Consume data from the fuzzer input
    char desc_index = stream.ConsumeIntegral<char>();
    int length = stream.ConsumeIntegral<int>();
    std::vector<char> data_vector = stream.ConsumeBytes<char>(length);

    // Call the function to fuzz
    libusb_get_string_descriptor_ascii(dev_handle, desc_index, data_vector.data(), length);

    // Cleanup
    libusb_close(dev_handle);
    libusb_exit(ctx);

    return 0;
}