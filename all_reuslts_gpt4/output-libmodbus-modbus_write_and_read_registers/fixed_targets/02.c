#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "modbus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a Modbus context
  modbus_t *ctx = modbus_new_tcp("127.0.0.1", 1502);
  if (ctx == NULL) {
    return 0;
  }

  // Consume data for write and read addresses
  int write_addr = stream.ConsumeIntegral<int>();
  int read_addr = stream.ConsumeIntegral<int>();

  // Consume data for write and read register numbers
  int write_nb = stream.ConsumeIntegralInRange<int>(1, 100); // assuming max 100 registers
  int read_nb = stream.ConsumeIntegralInRange<int>(1, 100); // assuming max 100 registers

  // Create source and destination buffers
  std::vector<short> src(write_nb);
  std::vector<short> dest(read_nb);

  // Consume data for source registers
  for (int i = 0; i < write_nb; ++i) {
    src[i] = stream.ConsumeIntegral<short>();
  }

  // Call the target function
  modbus_write_and_read_registers(ctx, write_addr, write_nb, src.data(), read_addr, read_nb, dest.data());

  // Clean up
  modbus_free(ctx);

  return 0;
}