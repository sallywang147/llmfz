#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "modbus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int addr = stream.ConsumeIntegral<int>();
  int nb = stream.ConsumeIntegral<int>();

  std::vector<short> dest(nb);

  modbus_t* ctx = modbus_new_tcp("127.0.0.1", 502);
  if (ctx == nullptr) {
    return 0;
  }

  modbus_set_debug(ctx, TRUE);

  if (modbus_connect(ctx) == -1) {
    modbus_free(ctx);
    return 0;
  }

  modbus_read_input_registers(ctx, addr, nb, dest.data());

  modbus_close(ctx);
  modbus_free(ctx);

  return 0;
}