#include <fuzzer/FuzzedDataProvider.h>
#include <coap3/coap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct coap_context_t* context = coap_new_context(nullptr);
  if (context == nullptr) {
    return 0;
  }

  std::string arg2 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 3);
  std::string arg3 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string arg4 = stream.ConsumeRemainingBytesAsString();

  int arg5 = stream.ConsumeIntegral<int>();

  coap_persist_startup_locked(context, const_cast<char*>(arg2.c_str()), const_cast<char*>(arg3.c_str()), const_cast<char*>(arg4.c_str()), arg5);

  coap_free_context(context);

  return 0;
}