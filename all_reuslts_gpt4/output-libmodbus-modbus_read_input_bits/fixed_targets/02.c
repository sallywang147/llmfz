#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "modbus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a Modbus context
  modbus_t *ctx = modbus_new_tcp("127.0.0.1", 1502);
  if (ctx == NULL) {
    return 0;
  }

  // Extract the address and number of bits to read
  int addr = stream.ConsumeIntegral<int>();
  int nb = stream.ConsumeIntegral<int>();

  // Create a buffer to store the result
  std::vector<char> dest(nb);

  // Call the function to fuzz
  modbus_read_input_bits(ctx, addr, nb, dest.data());

  // Clean up
  modbus_close(ctx);
  modbus_free(ctx);

  return 0;
}