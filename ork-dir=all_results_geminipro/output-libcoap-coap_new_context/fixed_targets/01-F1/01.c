#include <coap3/coap.h>

extern "C" {
#include <coap3/coap_debug.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct coap_address_t addr;
  coap_address_init(&addr);

  struct coap_context_t *ctx = coap_new_context(&addr);
  if (ctx) {
    coap_delete_context(ctx);
  }
  return 0;
}