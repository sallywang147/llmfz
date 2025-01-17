#include <fuzzer/FuzzedDataProvider.h>
#include <modbus/modbus.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize modbus context
  modbus_t *ctx = modbus_new_rtu("/dev/ptmx", 9600, 'N', 8, 1);
  if (ctx == NULL) {
    return 0; // Failed to allocate modbus context
  }

  // Consume data for address and number of bits
  int addr = stream.ConsumeIntegral<int>();
  int nb = stream.ConsumeIntegral<int>();

  // Create a vector for the destination buffer
  std::vector<char> dest(nb);

  // Call the function under test
  modbus_read_input_bits(ctx, addr, nb, dest.data());

  // Clean up
  modbus_free(ctx);

  return 0;
}