#include <fuzzer/FuzzedDataProvider.h>
#include <coap3/coap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    // Not enough data to proceed.
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  coap_context_t *ctx = coap_new_context(nullptr);
  if (ctx == nullptr) {
    // Failed to create context.
    return 0;
  }

  // Divide the data into four parts for the four string parameters.
  size_t part_size = size / 4;
  std::string param1 = stream.ConsumeBytesAsString(part_size);
  std::string param2 = stream.ConsumeBytesAsString(part_size);
  std::string param3 = stream.ConsumeBytesAsString(part_size);

  // Consume the remaining data for the integer parameter.
  int param4 = stream.ConsumeIntegral<int>();

  coap_persist_startup_locked(ctx, param1.data(), param2.data(), param3.data(), param4);

  coap_free_context(ctx);
  return 0;
}