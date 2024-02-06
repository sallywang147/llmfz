#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "modbus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize modbus context
  modbus_t* ctx = modbus_new_tcp("127.0.0.1", 502);
  if (ctx == nullptr) {
    return 0;
  }

  // Get max_dest from the fuzz data
  int max_dest = provider.ConsumeIntegral<int>();
  if (max_dest <= 0) {
    modbus_free(ctx);
    return 0;
  }

  // Create destination buffer
  std::vector<char> dest(max_dest);

  // Call the function under test
  int ret = modbus_report_slave_id(ctx, max_dest, dest.data());

  // Free the modbus context
  modbus_free(ctx);

  return 0;
}