#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "coap3/coap.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  coap_context_t* context = coap_new_context(nullptr);
  if (context == nullptr) {
    return 0;
  }

  std::string arg1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 3);
  std::string arg2 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string arg3 = stream.ConsumeBytesAsString(stream.remaining_bytes());
  int arg4 = stream.ConsumeIntegral<int>();

  coap_persist_startup(context, arg1.c_str(), arg2.c_str(), arg3.c_str(), arg4);

  coap_free_context(context);

  return 0;
}