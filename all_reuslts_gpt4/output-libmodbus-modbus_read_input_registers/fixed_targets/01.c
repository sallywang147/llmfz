#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "modbus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _modbus *ctx = modbus_new_tcp("127.0.0.1", 502);
  if (ctx == nullptr) {
    return 0;
  }

  int addr = stream.ConsumeIntegral<int>();
  int nb = stream.ConsumeIntegral<int>();

  // Ensure that nb is positive and less than MODBUS_MAX_READ_BITS to prevent overflow
  nb = nb > 0 ? nb : -nb;
  nb = nb % MODBUS_MAX_READ_BITS + 1;

  std::vector<short> dest(nb);

  modbus_read_input_registers(ctx, addr, nb, dest.data());

  modbus_free(ctx);

  return 0;
}