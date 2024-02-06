#include <fuzzer/FuzzedDataProvider.h>
#include <modbus/modbus.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    FuzzedDataProvider fuzzed_data(data, size);

    // Create a Modbus context
    modbus_t *ctx = modbus_new_tcp("127.0.0.1", 1502);
    if (ctx == NULL) {
        return 0;
    }

    // Extract an address and number of bits to write from the fuzzed data
    int addr = fuzzed_data.ConsumeIntegral<int>();
    int nb = fuzzed_data.ConsumeIntegral<int>();

    // Limit the number of bits to write to avoid buffer overflow
    if (nb > 8 * size || nb < 0) {
        nb = 8 * size;
    }

    // Allocate a buffer and fill it with the remaining fuzzed data
    char *src = (char *)malloc(nb);
    if (src == NULL) {
        modbus_free(ctx);
        return 0;
    }

    std::vector<uint8_t> remaining_bytes = fuzzed_data.ConsumeRemainingBytes<uint8_t>();
    memcpy(src, remaining_bytes.data(), remaining_bytes.size());

    // Call the function to be fuzzed
    modbus_write_bits(ctx, addr, nb, src);

    // Clean up
    free(src);
    modbus_free(ctx);

    return 0;
}