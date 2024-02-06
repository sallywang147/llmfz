#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "modbus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize modbus context
  modbus_t *ctx = modbus_new_tcp("127.0.0.1", 502);
  if (ctx == NULL) {
    fprintf(stderr, "Unable to allocate libmodbus context\n");
    return 0;
  }

  // Set debug mode
  modbus_set_debug(ctx, TRUE);

  // Connect to the server
  if (modbus_connect(ctx) == -1) {
    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
    modbus_free(ctx);
    return 0;
  }

  // Consume data from the fuzzer input
  int addr = stream.ConsumeIntegral<int>();
  int nb = stream.ConsumeIntegral<int>();
  std::string src = stream.ConsumeRemainingBytesAsString();

  // Call the function to be fuzzed
  modbus_write_bits(ctx, addr, nb, const_cast<char*>(src.c_str()));

  // Close the connection and free the context
  modbus_close(ctx);
  modbus_free(ctx);

  return 0;
}