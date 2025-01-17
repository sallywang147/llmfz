#include <fuzzer/FuzzedDataProvider.h>
#include "modbus/modbus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  
  // Initialize modbus context
  modbus_t *ctx = modbus_new_tcp("127.0.0.1", 502);
  if (ctx == NULL) {
    return 0;
  }

  // Define and initialize parameters for modbus_write_and_read_registers
  int write_addr = stream.ConsumeIntegral<int>();
  int write_nb = stream.ConsumeIntegral<int>();
  int read_addr = stream.ConsumeIntegral<int>();
  int read_nb = stream.ConsumeIntegral<int>();

  // Check if there is enough data left for src and dest arrays
  if (stream.remaining_bytes() < sizeof(short) * (write_nb + read_nb)) {
    modbus_free(ctx);
    return 0;
  }

  // Consume data for src and dest arrays
  std::vector<short> src(write_nb);
  std::vector<short> dest(read_nb);
  for (int i = 0; i < write_nb; i++) {
    src[i] = stream.ConsumeIntegral<short>();
  }
  for (int i = 0; i < read_nb; i++) {
    dest[i] = stream.ConsumeIntegral<short>();
  }

  // Call the target function
  modbus_write_and_read_registers(ctx, write_addr, write_nb, src.data(), read_addr, read_nb, dest.data());

  // Clean up
  modbus_free(ctx);

  return 0;
}