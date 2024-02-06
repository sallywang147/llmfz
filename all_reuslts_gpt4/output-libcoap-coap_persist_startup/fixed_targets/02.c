#include <fuzzer/FuzzedDataProvider.h>
#include <coap3/coap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a CoAP context
  coap_context_t *ctx = coap_new_context(nullptr);
  if (ctx == nullptr) {
    return 0;
  }

  // Consume data to create parameters for coap_persist_startup
  std::string param1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 3);
  std::string param2 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string param3 = stream.ConsumeRemainingBytesAsString();
  int param4 = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  coap_persist_startup(ctx, param1.data(), param2.data(), param3.data(), param4);

  // Clean up
  coap_free_context(ctx);

  return 0;
}