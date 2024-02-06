#include <fuzzer/FuzzedDataProvider.h>
#include <modbus/modbus.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  modbus_t *ctx = modbus_new_tcp("127.0.0.1", 502);
  if (ctx == nullptr) {
    return 0;
  }

  int max_dest = stream.ConsumeIntegralInRange<int>(1, 256);
  std::vector<char> dest(max_dest);

  modbus_report_slave_id(ctx, max_dest, dest.data());

  modbus_free(ctx);

  return 0;
}