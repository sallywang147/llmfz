#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "coap3/coap.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(coap_address_t)) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  coap_address_t address;
  provider.ConsumeData(&address, sizeof(address));

  coap_context_t* context = coap_new_context(&address);

  if (context) {
    coap_free_context(context);
  }

  return 0;
}